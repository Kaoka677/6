#  Đồ án môn học: Cấu trúc Dữ liệu và Giải thuật 
**Trường Đại học Khoa học Tự nhiên, ĐHQG TP.HCM**
## Hướng dẫn cách biên dịch và chạy mã nguồn
---
## 📁 Cấu trúc thư mục
~~~text
Project_Folder/
│
├── lib/                     # Thư viện Cấu trúc dữ liệu dùng chung (Templates)
│   ├── Algorithms.hpp, AVL.hpp, HashTable.hpp, Stack.hpp, PriorityQueue.hpp...
│
├── app/                     # Mã nguồn chính của Game
│   ├── Functions.hpp        # Khai báo struct và nguyên mẫu hàm
│   ├── Functions.cpp        # Triển khai logic (Combat, Crafting, Save/Load)
│   └── Main.cpp             # Vòng lặp game và Giao diện Console
│
├── data/                    # Thư mục chứa cơ sở dữ liệu (Database)
│   ├── items.csv            # Dữ liệu vật phẩm
│   ├── bosses.csv           # Dữ liệu quái vật
│   ├── recipes.csv          # Công thức chế tạo
│   ├── accounts.txt         # Lưu tài khoản và mật khẩu mã hóa
│   └── save_xxx.txt         # Lưu tiến trình nhân vật
│
├── Makefile                 # Kịch bản biên dịch tự động
└── README.md                #Hướng dẫn cách biên dịch và chạy mã nguồn
~~~
## Ý tưởng của game
Game được lấy ý tưởng từ các tự game cày cuốc để nhặt đồ và chiến đấu. Với việc áp dụng các thư viện được viết từ trước:
* `Stack` dùng để làm màn hình console trò chơi
* `Hashtable` dùng để lưu các dữ liệu nạp từ database
* `Algorithm` dùng để sắp xếp lại kho đồ người chơi
* `Priority Queue` dùng để làm hệ thống chiến đấu chiến đấu theo lượt
* `AVL` dùng để làm hệ thống kho đồ nhân vật

## Hướng dẫn biên dịch và chạy game
Dự án được biên dịch và chạy bằng `Makefile` tự động. 
#### Lưu ý khi chạy trên Windows cần thay đổi lệnh `system("clear")` trong `main.cpp` thành `system("cls")`
### 1. Yêu cầu hệ thống
Để biên dịch được mã nguồn, máy tính của bạn cần cài đặt sẵn:
* **Trình biên dịch C++:** `g++` (GCC) trên Linux/macOS, hoặc `MinGW` trên Windows.
* **Công cụ Make:** `make` trên Linux/macOS, hoặc `mingw32-make` trên Windows.

### 2. Cấu trúc thư mục bắt buộc
Trước khi chạy, hãy đảm bảo thư mục dự án có đủ cấu trúc sau:
~~~text
Project_Folder/
├── app/               # Chứa Functions.cpp, Functions.hpp, Main.cpp
├── lib/               # Chứa các file cấu trúc dữ liệu (.hpp)
├── data/              # BẮT BUỘC: Chứa items.csv, bosses.csv, recipes.csv
└── Makefile           # File kịch bản biên dịch
~~~
### 3. Lệnh chạy chương trình
Mở terminal ở thư mục `Project_Folder`
~~~
make clean #Dọn dẹp file cũ
make # Biên dịch mã nguòn
make run # Chạy chương trình
~~~

