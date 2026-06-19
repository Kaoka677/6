# Trình biên dịch C++
CXX = g++

# Cờ biên dịch: 
# -Wall: Hiện tất cả cảnh báo lỗi
# -std=c++11: Dùng chuẩn C++11 (hoặc c++14/c++17 tùy máy bạn)
# -I./lib: Chỉ định cho trình biên dịch biết thư mục chứa các file .hpp của thư viện
CXXFLAGS = -Wall -std=c++11 -I./lib

# Tên file thực thi đầu ra
TARGET = game

# Các file mã nguồn của ứng dụng (nằm trong thư mục app)
SRCS = app/Main.cpp app/Functions.cpp

# Chuyển đổi tên file .cpp thành file object .o
OBJS = $(SRCS:.cpp=.o)

# Lệnh mặc định khi gõ "make"
all: $(TARGET)

# Quy tắc liên kết các file .o thành file thực thi
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)
	@echo "=> Bien dich thanh cong! Go 'make run' hoac './game' (tren Linux/Mac), 'game.exe' (tren Windows) de chay."

# Quy tắc biên dịch từng file .cpp thành .o
app/%.o: app/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Lệnh chạy tự động
run: all
	./$(TARGET)

# Lệnh dọn dẹp các file biên dịch tạm thời
clean:
	rm -f app/*.o $(TARGET) $(TARGET).exe
	@echo "=> Da don dep cac file .o va file thuc thi."
