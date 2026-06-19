#include "Functions.hpp"

int main()
{
	// Đọc dữ liệu và lưu vào bảng băm
	HashTable<string, string> accountDB(100);
	LoadAccounts("data/accounts.txt", accountDB);
	HashTable<string, Item> itemDB(100);
	LoadItemsFromFile("data/items.csv", itemDB);
	HashTable<string, Boss> bossDB(100);
	LoadBossesFromFile("data/bosses.csv", bossDB);
	HashTable<string, string> recipeDB(100);
	LoadRecipesFromFile("data/recipes.csv", recipeDB);

	// Màn hình đăng nhập game
	bool IsLoggedIn = false;
	string loggedInUser = "";
	while (!IsLoggedIn)
	{
		system("clear");
		cout << "====================================\n";
		cout << "      	    TRÒ CHƠI HIỆP SĨ         \n";
		cout << "====================================\n";
		cout << "[1]. Đăng nhập\n";
		cout << "[2]. Đăng ký tài khoản mới\n";
		cout << "[3]. Thoát game\n";
		cout << "Hãy nhập lựa chọn của bạn: ";

		int Choice;
		cin >> Choice;
		if (Choice == 1)
		{
			string user, pass;
			cout << "Tên đăng nhập: ";
			cin >> user;
			cout << "Mật khẩu: ";
			cin >> pass;

			string HashedPass = HashPassword(pass);
			string HashedUser = HashPassword(user);
			string *storedPass = accountDB.find(HashedUser);
			if (storedPass != nullptr && *storedPass == HashedPass)
			{
				cout << "\nĐăng nhập thành công Chào mừng " << user << ".\n";
				loggedInUser = user;
				IsLoggedIn = true;
				cout << "Nhấn Enter để tiếp tục";
				cin.ignore(256, '\n');
				cin.get();
			}
			else
			{
				cout << "\nSai tên đăng nhập hoặc mật khẩu. Vui lòng thử lại\n\n";
				cout << "Nhấn Enter để tiếp tục";
				cin.ignore(256, '\n');
				cin.get();
			}
		}
		else if (Choice == 2)
		{
			string user, pass;
			cout << "Nhập tên đăng nhập mới: ";
			cin >> user;

			if (accountDB.contains(user))
			{
				cout << "\nTên đăng nhập đã tồn tại. Hãy chọn tên khác\n\n";
				cout << "Nhấn Enter để tiếp tục";
				cin.ignore(256, '\n');
				cin.get();
			}
			else
			{
				cout << "Nhập mật khẩu: ";
				cin >> pass;

				string HashedPass = HashPassword(pass);
				string HasedUser = HashPassword(user);

				accountDB.insert(HasedUser, HashedPass);
				SaveAccount("data/accounts.txt", HasedUser, HashedPass);

				cout << "\nĐăng ký thành công Bạn có thể đăng nhập ngay.\n\n";
				cout << "Nhấn Enter để tiếp tục";
				cin.ignore(256, '\n');
				cin.get();
			}
		}
		else if (Choice == 3)
		{
			cout << "Hẹn gặp lại\n";
			return 0;
		}
	}

	// Bắt đầu nạp dữ liệu người chơi
	system("clear");
	string SaveFile = "data/save_" + loggedInUser + ".txt";
	Player CurrentPlayer(loggedInUser);

	if (LoadFromFile(CurrentPlayer, SaveFile, itemDB))
	{
		cout << "Đã tải tiến trình chơi của " << loggedInUser << ".\n";
		cout << "Bạn hiện đang có " << CurrentPlayer.inventory.size() << " loại vật phẩm trong túi.\n";
	}
	else
	{
		cout << "Tạo file lưu mới cho " << loggedInUser << ".\n";

		Item *StarterWeapon = itemDB.find("wpn_01");
		Item *StarterPotion = itemDB.find("csm_01");

		if (StarterWeapon)
		{
			CurrentPlayer.inventory.insert(*StarterWeapon);
			EquipItem(CurrentPlayer, "wpn_01");
		}
		if (StarterPotion)
		{
			Item potions = *StarterPotion;
			potions.quantity = 5;
			CurrentPlayer.inventory.insert(potions);
		}

		SaveTofile(CurrentPlayer, SaveFile);
	}
	cout << "\nNhấn Enter để bắt đầu trò chơi";
	cin.get();

	// Vào màn hình chính
	Stack<string> uiStack;
	uiStack.push("MAIN_MENU");
	int SortMode = 0;

	while (!uiStack.empty())
	{
		system("clear");
		string CurrentState = uiStack.top();
		if (CurrentState == "MAIN_MENU")
		{
			cout << "====================================\n";
			cout << "			  Làng tân thủ           \n";
			cout << "====================================\n";
			cout << "Nhân vật: " << CurrentPlayer.name << " | HP: " << CurrentPlayer.hp << "/" << CurrentPlayer.maxHp << "\n";
			cout << "Sát thương: " << TotalAttack(CurrentPlayer) << " | Giáp: " << TotalDefense(CurrentPlayer) << "\n";
			cout << "Vũ khí: " << (CurrentPlayer.equippedWeapon ? CurrentPlayer.equippedWeapon->name : "[Chưa trang bị]") << "\n";
			cout << "Áo giáp: " << (CurrentPlayer.equippedArmor ? CurrentPlayer.equippedArmor->name : "[Chưa trang bị]") << "\n";
			cout << "[1]. Xem Túi đồ \n";
			cout << "[2]. Đi thám hiểm \n";
			cout << "[3]. Bàn chế tạo \n";
			cout << "[4]. Lưu và đăng xuất\n";
			cout << "Hãy nhập lựa chọn của bạn: ";

			int Choice;
			cin >> Choice;
			if (Choice == 1)
			{
				uiStack.push("INVENTORY_MENU");
			}
			else if (Choice == 2)
			{
				uiStack.push("BOSS_MENU");
			}
			else if (Choice == 3)
			{
				uiStack.push("CRAFTING_MENU");
			}
			else if (Choice == 4)
			{
				SaveTofile(CurrentPlayer, SaveFile);
				uiStack.pop();
			}
		}
		else if (CurrentState == "INVENTORY_MENU")
		{
			cout << "====================================\n";
			cout << "              TÚI ĐỒ                \n";
			cout << "====================================\n";
			int InvSize = CurrentPlayer.inventory.size();
			Item *InvArray = nullptr;

			if (InvSize == 0)
			{
				cout << "Túi đồ của bạn đang trống rỗng\n";
			}
			else
			{
				InvArray = CurrentPlayer.inventory.toArray();
				if (SortMode == 1)
				{
					Algorithms::mergeSort(InvArray, InvSize, CompareWeight());
					cout << "(Chế độ lọc: Trọng lượng giảm dần)\n";
				}
				else if (SortMode == 2)
				{
					Algorithms::mergeSort(InvArray, InvSize, CompareValue());
					cout << "(Chế độ lọc: Giá trị giảm dần)\n";
				}
				else if (SortMode == 0)
				{
					Algorithms::mergeSort(InvArray, InvSize, CompareName());
					cout << "(Chế độ lọc: Mặc định theo ID)\n";
				}

				for (int i = 0; i < InvSize; i++)
				{
					cout << "[" << i + 1 << "] " << InvArray[i].name
						 << " | Số lượng: " << InvArray[i].quantity
						 << " | Cân Nặng: " << InvArray[i].weight << "g"
						 << " | Giá Trị: " << InvArray[i].value << "\n";
				}
			}

			cout << "\n[1]. Trang bị vật phẩm\n";
			cout << "[2]. Sắp xếp túi đồ\n";
			cout << "[3]. Vứt vật phẩm\n";
			cout << "[0]. Quay lại\n";
			cout << "Hãy nhập lựa chọn của bạn: ";

			int Choice;
			cin >> Choice;

			if (Choice == 1)
			{
				if (InvSize == 0)
				{
					cout << "Túi đồ trống, không có gì để trang bị\n";
				}
				else
				{
					int ItemIndex;
					cout << "Nhập số thứ tự vật phẩm (1 - " << InvSize << "): ";
					cin >> ItemIndex;

					if (ItemIndex >= 1 && ItemIndex <= InvSize)
					{
						string UseItem = InvArray[ItemIndex - 1].id;
						EquipItem(CurrentPlayer, UseItem);
					}
					else
					{
						cout << "Số thứ tự không hợp lệ\n";
					}
				}
				cout << "Nhấn Enter để tiếp tục";
				cin.ignore(256, '\n');
				cin.get();
			}
			else if (Choice == 2)
			{
				uiStack.push("SORT_MENU");
			}
			else if (Choice == 3)
			{
				if (InvSize == 0)
				{
					cout << "Túi đồ trống, không có gì để vứt\n";
				}
				else
				{
					cout << "-> Nhập sô thứ tự vật phẩm muốn vứt (1 - " << InvSize << "): ";
					int ItemIndex;
					cin >> ItemIndex;

					if (ItemIndex >= 1 && ItemIndex <= InvSize)
					{
						int dropQty;
						cout << "-> Nhập số lượng muốn vứt (đang có " << InvArray[ItemIndex - 1].quantity << "): ";
						cin >> dropQty;

						if (dropQty > 0 && dropQty <= InvArray[ItemIndex - 1].quantity)
						{
							string idToDrop = InvArray[ItemIndex - 1].id;
							DropItem(CurrentPlayer, idToDrop, dropQty);
						}
						else
						{
							cout << "Số lượng vứt không hợp lệ\n";
						}
					}
					else
					{
						cout << "Số thứ tự không hợp lệ\n";
					}
				}
			}
			else if (Choice == 0)
			{
				uiStack.pop();
			}

			if (InvArray != nullptr)
			{
				delete[] InvArray;
			}
		}
		else if (CurrentState == "BOSS_MENU")
		{
			cout << "====================================\n";
			cout << "         DANH SÁCH MỤC TIÊU         \n";
			cout << "====================================\n";
			cout << "[boss_01] Sói Điên Đột Biến (Rớt: Răng Sói)\n";
			cout << "[boss_02] Mộc Yêu Ngàn Năm  (Rớt: Gỗ Ma Quỷ)\n\n";
			cout << "[boss_03] Hiệp Sĩ Lưu Vong  (Rớt: Mảnh Thép Vỡ)\n";
			cout << "[boss_04] Golem Đá Cổ Đại   (Rớt: Đá Cổ Ngữ)\n\n";
			cout << "[boss_05] Chúa Tể Bóng Tối  (Rớt: Vũ Khí Của Chúa Tể)\n";
			cout << "------------------------------------\n";
			cout << "Nhập ID quái vật bạn muốn khiêu chiến (hoặc gõ 0 để hủy): ";
			string bossId;
			cin >> bossId;
			Boss *targetBoss = bossDB.find(bossId);
			if (targetBoss)
			{
				Combat(CurrentPlayer, *targetBoss, itemDB);
				uiStack.pop();
			}
			else
			{
				cout << "Không tìm thấy quái vật này\n";
				cout << "Nhấn Enter để tiếp tục";
				cin.ignore(256, '\n');
				cin.get();
				uiStack.pop();
			}
		}
		else if (CurrentState == "SORT_MENU")
		{
			cout << "====================================\n";
			cout << "          SẮP XẾP TÚI ĐỒ            \n";
			cout << "====================================\n";
			cout << "[1]. Sắp xếp mặc định \n";
			cout << "[2]. Trọng lượng giảm dần \n";
			cout << "[3]. Giá trị giảm dần \n";
			cout << "[0]. Hủy\n";
			cout << "Hãy nhập lựa chọn của bạn: ";

			int Choice;
			cin >> Choice;
			if (Choice == 1)
				SortMode = 0;
			else if (Choice == 2)
				SortMode = 1;
			else if (Choice == 3)
				SortMode = 2;
			uiStack.pop();
		}
		else if (CurrentState == "CRAFTING_MENU")
		{
			cout << "====================================\n";
			cout << "            	LÒ RÈN	 	         \n";
			cout << "====================================\n";
			cout << "[1]. Xem sổ tay công thức\n";
			cout << "[2]. Tiến hành ghép đồ\n";
			cout << "[0]. Quay lại\n";
			cout << "Chọn: ";
			int Choice;
			cin >> Choice;
			if (Choice == 1)
			{
				uiStack.push("RECIPE_MENU");
			}
			else if (Choice == 2)
			{
				string id1, id2;
				cout << "-> Nhập ID nguyên liệu 1: ";
				cin >> id1;
				cout << "-> Nhập ID nguyên liệu 2: ";
				cin >> id2;
				CraftItem(CurrentPlayer, id1, id2, recipeDB, itemDB);

				cout << "Nhấn Enter để tiếp tục...";
				cin.ignore(256, '\n');
				cin.get();
			}
			else if (Choice == 0)
			{
				uiStack.pop();
			}
		}
		else if (CurrentState == "RECIPE_MENU")
		{
			cout << "====================================\n";
			cout << "           SỔ TAY CÔNG THỨC         \n";
			cout << "====================================\n";
			cout << "[ NGUYÊN LIỆU ]\n";
			cout << "- Răng Sói (mat_w1) + Răng Sói (mat_w1) = Nanh Sói Cứng (Cấp 2)\n";
			cout << "- Nanh Sói Cứng (mat_w2) + Nanh Sói Cứng (mat_w2) = Tinh Thể Sói (Cấp 3)\n";
			cout << "- Gỗ Ma Quỷ (mat_t1) + Gỗ Ma Quỷ (mat_t1) = Gỗ Cường Hóa (Cấp 2)\n";
			cout << "- Gỗ Cường Hóa (mat_t2) + Gỗ Cường Hóa (mat_t2) = Lõi Cây Thuần Khiết (Cấp 3)\n\n";
			cout << "- Mảnh Thép Vỡ (mat_s1) + Mảnh Thép Vỡ (mat_s1) = Thỏi Thép Đen (Cấp 2)\n";
			cout << "- Đá Cổ Ngữ (mat_g1) + Đá Cổ Ngữ (mat_g1) = Lõi Golem (Cấp 2)\n\n";
			cout << "[ TRANG BỊ ]\n";
			cout << "- Tinh Thể Sói (mat_w3) + Lõi Cây Thuần Khiết (mat_t3) = Kiếm Vuốt Sói\n";
			cout << "- Tinh Thể Sói (mat_w3) + Tinh Thể Sói (mat_w3) = Giáp Da Sói\n\n";
			cout << "- Thỏi Thép Đen (mat_s2) + Lõi Golem (mat_g2) = Đại Kiếm Thép Đen\n";
			cout << "- Thỏi Thép Đen (mat_s2) + Thỏi Thép Đen (mat_s2) = Giáp Thép Nặng\n\n";
			cout << "[ VẬT PHẨM HỒI PHỤC ]\n";
			cout << "- Răng Sói (mat_w1) + Gỗ Ma Quỷ (mat_t1) = Bình Máu Nhỏ\n";
			cout << "- Bình Máu Nhỏ (csm_01) + Bình Máu Nhỏ (csm_01) = Bình Máu Lớn\n";
			cout << "------------------------------------\n";
			cout << "[0]. Quay lại\n";
			cout << "Chọn: ";
			int Choice;
			cin >> Choice;
			if (Choice == 0)
			{
				uiStack.pop();
			}
		}
	}
	return 0;
}
