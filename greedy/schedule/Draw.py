import matplotlib.pyplot as plt

# 读取数据规模（data.txt）
with open('datascale3.txt', 'r') as f:
    data = f.read().splitlines()  # 每行数据为一个元素
    # 假设数据格式是空格分隔，我们用map将其转换为整数或浮动数
    x = [float(i) for i in data[0].split()]  # 数据规模

# 读取运行时间（file.txt）
with open('sort.txt', 'r') as f:
    time_data = f.read().splitlines()
    y = [float(i) for i in time_data[0].split()]  # 运行时间

# 绘制图形
plt.plot(x, y, marker='o', color='b', linestyle='-', label='Time vs Data Size')

# 设置图表标题和坐标轴标签
plt.title('Data Size vs Running Time')
plt.xlabel('Data Size')
plt.ylabel('Running Time (s)')
plt.legend()

# 显示图形
plt.show()
