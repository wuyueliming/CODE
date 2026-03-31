# 编译器设置
CXX = g++
CXXFLAGS = -std=c++17 -Wall -g
LDFLAGS = -lpthread

# 源文件列表（只包含必需的 .cpp 文件，不含 BenchMark.cpp 因为它有独立的 main）
SRCS = test.cpp CentralCache.cpp PageCache.cpp ThreadCache.cpp string.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = mystl

# 默认目标
.PHONY: all clean

all: $(TARGET)

# 链接生成可执行文件
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# 编译 .cpp 为 .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 清理
clean:
	rm -f $(OBJS) $(TARGET)