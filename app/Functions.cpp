#include "Functions.hpp"
#include <sstream>
#include <fstream>
#include <functional>

Item::Item()
{
    id = "";
    name = "";
    type = "";
    attack = 0;
    defense = 0;
    value = 0;
    weight = 0;
    quantity = 0;
}

Item::Item(string i, string n, string t, int a, int d, int v, int w, int q)
{
    id = i;
    name = n;
    type = t;
    attack = a;
    defense = d;
    value = v;
    weight = w;
    quantity = q;
}

Player::Player(string n)
{
    name = n;
    maxHp = 100;
    hp = maxHp;
    baseAttack = 5;
    baseDefense = 2;
    speed = 10;
    currentWeight = 0;
    equippedWeapon = nullptr;
    equippedArmor = nullptr;
}

Boss::Boss() : id(""), name(""), hp(0), attack(0), defense(0), speed(0), dropItemId("") {}

Boss::Boss(string i, string n, int h, int a, int d, int s, string drop)
    : id(i), name(n), hp(h), attack(a), defense(d), speed(s), dropItemId(drop) {}

string HashPassword(const string &pass)
{
    hash<string> hasher;
    return to_string(hasher(pass));
}

void LoadItemsFromFile(const string &filename, HashTable<string, Item> &itemDB)
{
    ifstream file(filename);
    if (!file.is_open())
        return;

    string line;
    while (getline(file, line))
    {
        if (line.empty() || line[0] == '#')
            continue;
        if (line.back() == '\r')
            line.pop_back();

        stringstream ss(line);
        string id, name, type, tempStr;
        int value = 0, weight = 0, attack = 0, defense = 0;

        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, type, ',');

        getline(ss, tempStr, ',');
        if (!tempStr.empty())
            value = stoi(tempStr);
        getline(ss, tempStr, ',');
        if (!tempStr.empty())
            weight = stoi(tempStr);
        getline(ss, tempStr, ',');
        if (!tempStr.empty())
            attack = stoi(tempStr);
        getline(ss, tempStr, ',');
        if (!tempStr.empty())
            defense = stoi(tempStr);

        itemDB.insert(id, Item(id, name, type, attack, defense, value, weight, 1));
    }
    file.close();
}

void LoadBossesFromFile(const string &filename, HashTable<string, Boss> &bossDB)
{
    ifstream file(filename);
    if (!file.is_open())
        return;

    string line;
    while (getline(file, line))
    {
        if (line.empty() || line[0] == '#')
            continue;
        if (line.back() == '\r')
            line.pop_back();

        stringstream ss(line);
        string id, name, tempStr, drop;
        int hp = 0, attack = 0, defense = 0, speed = 0;

        getline(ss, id, ',');
        getline(ss, name, ',');

        getline(ss, tempStr, ',');
        if (!tempStr.empty())
            hp = stoi(tempStr);
        getline(ss, tempStr, ',');
        if (!tempStr.empty())
            attack = stoi(tempStr);
        getline(ss, tempStr, ',');
        if (!tempStr.empty())
            defense = stoi(tempStr);
        getline(ss, tempStr, ',');
        if (!tempStr.empty())
            speed = stoi(tempStr);

        getline(ss, drop, ',');

        bossDB.insert(id, Boss(id, name, hp, attack, defense, speed, drop));
    }
    file.close();
}

void LoadRecipesFromFile(const string &filename, HashTable<string, string> &recipeDB)
{
    ifstream file(filename);
    if (!file.is_open())
        return;

    string line;
    while (getline(file, line))
    {
        if (line.empty() || line[0] == '#')
            continue;
        if (line.back() == '\r')
            line.pop_back();

        stringstream ss(line);
        string id1, id2, resultId;

        getline(ss, id1, ',');
        getline(ss, id2, ',');
        getline(ss, resultId, ',');

        string key = (id1 < id2) ? (id1 + "+" + id2) : (id2 + "+" + id1);
        recipeDB.insert(key, resultId);
    }
    file.close();
}

void LoadAccounts(const string &filename, HashTable<string, string> &accDB)
{
    ifstream file(filename);
    if (!file.is_open())
        return;

    string user, pass;
    while (file >> user >> pass)
    {
        accDB.insert(user, pass);
    }
    file.close();
}

void SaveAccount(const string &filename, const string &user, const string &pass)
{
    ofstream file(filename, ios::app);
    if (file.is_open())
    {
        file << user << " " << pass << "\n";
        file.close();
    }
}

int TotalAttack(const Player &player)
{
    int total = player.baseAttack;
    if (player.equippedWeapon != nullptr)
        total += player.equippedWeapon->attack;
    return total;
}

int TotalDefense(const Player &player)
{
    int total = player.baseDefense;
    if (player.equippedArmor != nullptr)
        total += player.equippedArmor->defense;
    return total;
}

int TotalWeight(const Player &player)
{
    int total = 0;
    if (player.inventory.size() == 0)
        return 0;

    Item *arr = player.inventory.toArray();
    if (arr)
    {
        for (int i = 0; i < player.inventory.size(); i++)
            total += arr[i].weight * arr[i].quantity;
        delete[] arr;
    }
    return total;
}
void UnequipWeapon(Player &player)
{
    if (player.equippedWeapon != nullptr)
    {
        cout << "Đã tháo vũ khí: " << player.equippedWeapon->name << "\n";
        player.equippedWeapon = nullptr;
    }
}

void UnequipArmor(Player &player)
{
    if (player.equippedArmor != nullptr)
    {
        cout << "Đã tháo áo giáp: " << player.equippedArmor->name << "\n";
        player.equippedArmor = nullptr;
    }
}

void EquipItem(Player &player, const string &itemId)
{
    AVLNode<Item> *node = player.inventory.searchNode(Item(itemId, "", "", 0, 0, 0, 0, 0));
    if (!node)
        return;

    Item *itemToEquip = &node->data;

    if (itemToEquip->type == "Weapon")
    {
        UnequipWeapon(player);
        player.equippedWeapon = itemToEquip;
        cout << "Đã trang bị vũ khí: " << player.equippedWeapon->name << "\n";
    }
    else if (itemToEquip->type == "Armor")
    {
        UnequipArmor(player);
        player.equippedArmor = itemToEquip;
        cout << "Đã mặc giáp: " << player.equippedArmor->name << "\n";
    }
    else
    {
        cout << itemToEquip->name << " không thể trang bị được!\n";
    }
}
void DropItem(Player &player, const string &itemId, int amount)
{
    AVLNode<Item> *node = player.inventory.searchNode(Item(itemId, "", "", 0, 0, 0, 0, 0));
    if (!node)
        return;
    if (node->data.quantity - amount <= 0)
    {
        if (player.equippedWeapon != nullptr && player.equippedWeapon->id == itemId)
        {
            UnequipWeapon(player);
        }
        if (player.equippedArmor != nullptr && player.equippedArmor->id == itemId)
        {
            UnequipArmor(player);
        }
    }

    node->data.quantity -= amount;
    cout << "Đã vứt bỏ " << amount << " " << node->data.name << " ra khỏi túi đồ.\n";
    if (node->data.quantity <= 0)
    {
        player.inventory.remove(node->data);
    }
}

void SaveTofile(const Player &player, const string &filename)
{
    ofstream file(filename);
    if (file.is_open())
    {
        file << player.name << "\n"
             << player.hp << "\n"
             << player.maxHp << "\n"
             << player.baseAttack << "\n"
             << player.baseDefense << "\n"
             << player.speed << "\n";

        file << (player.equippedWeapon ? player.equippedWeapon->id : "NONE") << "\n";
        file << (player.equippedArmor ? player.equippedArmor->id : "NONE") << "\n";

        int invSize = player.inventory.size();
        file << invSize << "\n";

        Item *invArray = player.inventory.toArray();
        if (invArray)
        {
            for (int i = 0; i < invSize; i++)
            {
                file << invArray[i].id << " " << invArray[i].quantity << "\n";
            }
            delete[] invArray;
        }

        file.close();
        cout << "\nĐÃ LƯU TIẾN TRÌNH THÀNH CÔNG!\n";
    }
    else
        cout << "\nKhông lưu được tiến trình!\n";
}

bool LoadFromFile(Player &player, const string &filename, const HashTable<string, Item> &itemDB)
{
    ifstream file(filename);
    if (file.is_open())
    {
        getline(file, player.name);
        file >> player.hp >> player.maxHp >> player.baseAttack >> player.baseDefense >> player.speed;

        string weaponId, armorId;
        file >> weaponId >> armorId;

        int invSize;
        file >> invSize;

        player.inventory.clear();

        for (int i = 0; i < invSize; i++)
        {
            string itemId;
            int quantity;
            file >> itemId >> quantity;

            Item *dbItem = itemDB.find(itemId);
            if (dbItem)
            {
                Item newItem = *dbItem;
                newItem.quantity = quantity;
                player.inventory.insert(newItem);
            }
        }
        file.close();

        player.equippedWeapon = nullptr;
        player.equippedArmor = nullptr;
        if (weaponId != "NONE")
            EquipItem(player, weaponId);
        if (armorId != "NONE")
            EquipItem(player, armorId);

        return true;
    }
    return false;
}

void Combat(Player &player, Boss boss, const HashTable<string, Item> &itemDB)
{
    cout << "\n====================================\n";
    cout << "        TRẬN CHIẾN BẮT ĐẦU!         \n";
    cout << "====================================\n";
    cout << "Kẻ địch: " << boss.name << " (HP: " << boss.hp << " / Sát thương: " << boss.attack << ")\n";

    int maxWeight = 50000;
    int playerSpeed = player.speed;

    if (TotalWeight(player) > maxWeight)
    {
        playerSpeed /= 2;
        cout << "\nTúi đồ quá nặng (>50kg)! Tốc độ của bạn bị giảm một nửa!\n";
    }

    int round = 1;
    while (player.hp > 0 && boss.hp > 0)
    {
        cout << "\n--- HIỆP " << round++ << " ---\n";

        PriorityQueue<string> turnQueue;
        turnQueue.insert("PLAYER", playerSpeed);
        turnQueue.insert("BOSS", boss.speed);

        while (!turnQueue.empty() && player.hp > 0 && boss.hp > 0)
        {
            string currentTurn = turnQueue.peek();
            turnQueue.extract();

            if (currentTurn == "PLAYER")
            {
                cout << "\n>> Lượt của " << player.name << " (HP: " << player.hp << "/" << player.maxHp << ")\n";
                cout << "[1]. Tấn công thường\n";
                cout << "[2]. Dùng Bình Máu Nhỏ (Hồi 50 HP)\n";
                cout << "Hành động: ";

                int choice;
                cin >> choice;

                if (choice == 1)
                {
                    int pAtk = TotalAttack(player);
                    int dmg = (pAtk - boss.defense > 0) ? (pAtk - boss.defense) : 1;
                    boss.hp -= dmg;
                    cout << "Bạn tấn công " << boss.name << ", gây " << dmg << " sát thương!\n";
                    cout << "Máu của boss: " << boss.hp << "\n";
                }
                else if (choice == 2)
                {
                    AVLNode<Item> *potionNode = player.inventory.searchNode(Item("csm_01", "", "", 0, 0, 0, 0, 0));
                    if (potionNode && potionNode->data.quantity > 0)
                    {
                        potionNode->data.quantity--;
                        player.hp = (player.hp + 50 > player.maxHp) ? player.maxHp : (player.hp + 50);
                        cout << "Bạn uống Bình Máu Nhỏ, hồi 50 HP!\n";
                        if (potionNode->data.quantity == 0)
                            player.inventory.remove(potionNode->data);
                    }
                    else
                        cout << "Bạn không có Bình Máu Nhỏ! Bạn bị mất lượt!\n";
                }
            }
            else
            {
                cout << "\n>> Lượt của " << boss.name << "\n";
                int bAtk = boss.attack;
                int pDef = TotalDefense(player);
                int dmg = (bAtk - pDef > 0) ? (bAtk - pDef) : 1;

                player.hp -= dmg;
                cout << "" << boss.name << " đánh trúng bạn, gây " << dmg << " sát thương!\n";
            }
        }
    }

    if (player.hp <= 0)
    {
        cout << "\nBạn đã chết hãy cày tiếp\n";
        player.hp = 100;
    }
    else if (boss.hp <= 0)
    {
        cout << "\nBạn đã tiêu diệt " << boss.name << "\n";
        if (boss.dropItemId != "")
        {
            Item *drop = itemDB.find(boss.dropItemId);
            if (drop)
            {
                cout << "=> Vật phẩm rớt ra: " << drop->name << "\n";
                AVLNode<Item> *existNode = player.inventory.searchNode(*drop);
                if (existNode)
                    existNode->data.quantity++;
                else
                    player.inventory.insert(*drop);
            }
        }
    }
    cout << "\nNhấn Enter để trở về Làng...";
    cin.ignore(256, '\n');
    cin.get();
}

void CraftItem(Player &player, const string &id1, const string &id2, const HashTable<string, string> &recipeDB, const HashTable<string, Item> &itemDB)
{
    AVLNode<Item> *node1 = player.inventory.searchNode(Item(id1, "", "", 0, 0, 0, 0, 0));
    if (!node1)
    {
        cout << "Bạn không có nguyên liệu " << id1 << "!\n";
        return;
    }

    AVLNode<Item> *node2 = player.inventory.searchNode(Item(id2, "", "", 0, 0, 0, 0, 0));
    if (!node2)
    {
        cout << "Bạn không có nguyên liệu " << id2 << "!\n";
        return;
    }

    if (id1 == id2 && node1->data.quantity < 2)
    {
        cout << "Bạn cần ít nhất 2 món " << node1->data.name << " để ghép!\n";
        return;
    }

    string key = (id1 < id2) ? (id1 + "+" + id2) : (id2 + "+" + id1);
    string *resultId = recipeDB.find(key);

    if (!resultId)
    {
        cout << "Không có công thức nào để ghép 2 món này!\n";
        return;
    }

    Item *resultItem = itemDB.find(*resultId);
    if (!resultItem)
        return;

    Item item1 = node1->data;
    Item item2 = node2->data;

    if (id1 == id2)
    {
        node1->data.quantity -= 2;
        if (node1->data.quantity == 0)
            player.inventory.remove(item1);
    }
    else
    {
        node1->data.quantity -= 1;
        if (node1->data.quantity == 0)
            player.inventory.remove(item1);

        AVLNode<Item> *n2 = player.inventory.searchNode(item2);
        if (n2)
        {
            n2->data.quantity -= 1;
            if (n2->data.quantity == 0)
                player.inventory.remove(item2);
        }
    }

    AVLNode<Item> *existNode = player.inventory.searchNode(*resultItem);
    if (existNode)
        existNode->data.quantity++;
    else
        player.inventory.insert(*resultItem);

    cout << "Bạn nhận được: " << resultItem->name << "\n";
}