import matplotlib.pyplot as plt

# 读取数据规模（datascale.txt）
with open('datascale.txt', 'r') as f:
    data = f.read().splitlines()  # 每行数据为一个元素
    x = []  # 用于存储数据规模
    for line in data:
        x.extend(map(float, line.split()))  # 逐行处理，并将每行的数据扩展到x中

# 读取运行时间（dp3.txt）
with open('dp3.txt', 'r') as f:
    time_data = f.read().splitlines()  # 每行数据为一个元素
    y = []  # 用于存储运行时间
    for line in time_data:
        y.extend(map(float, line.split()))  # 逐行处理，并将每行的数据扩展到y中

# 绘制图形
plt.plot(x, y, marker='o', color='b', linestyle='-', label='Time vs Data Size')

# 设置图表标题和坐标轴标签
plt.title('dp3')
plt.xlabel('Data Size')
plt.ylabel('Running Time (s)')
plt.legend()

# 显示图形
plt.show()
