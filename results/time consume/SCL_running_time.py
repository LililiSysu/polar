import matplotlib.pyplot as plt

#1 基础绘图
#第1步：定义x和y坐标轴上的点   x坐标轴上点的数值
N = [ 64, 128, 256, 512, 1024 ]
#y坐标轴上点的数值
SCL_decode1 = [ 2.121000e-03, 4.966000e-03, 1.115800e-02, 2.546500e-02, 5.834300e-02 ]
SCL_decode2 = [ 1.503000e-03, 3.330000e-03, 7.997000e-03, 1.731900e-02, 3.792400e-02 ]
fast_SCL_decode = [ 1.430000e-03, 3.080000e-03, 7.180000e-03, 1.540000e-02, 3.299000e-02 ]
#第2步：使用plot绘制线条第1个参数是x的坐标值，第2个参数是y的坐标值
#plt.plot(x,y)

#2 定义绘图属性
'''
color：线条颜色，值r表示红色（red）
marker：点的形状，值o表示点为圆圈标记（circle marker）
linestyle：线条的形状，值dashed表示用虚线连接各点
'''
#plt.plot(x, y, color='r',marker='o',linestyle='dashed')
#plt.plot(x, y, 'ro')

p1,=plt.plot(N,SCL_decode1,marker='o')
p2,=plt.plot(N,SCL_decode2,marker='o')
p3,=plt.plot(N,fast_SCL_decode,marker='o')
'''
axis：坐标轴范围
语法为axis[xmin, xmax, ymin, ymax]，
也就是axis[x轴最小值, x轴最大值, y轴最小值, y轴最大值]
'''
#plt.axis([0, 6, 0, 20])


#对数坐标
#plt.xscale("log",base=2)
#plt.yscale("log")

#网格
plt.grid()

#设置y轴刻度
plt.xticks(N)

#3 给图片添加注释和标题等

#第2步：使用plot绘制线条 第1个参数是x的坐标值，第2个参数是y的坐标值
#plt.plot(x,y)
#添加文本 #x轴文本
plt.xlabel('N')
#y轴文本
plt.ylabel('time')
#标题
plt.title('SCL time consume verse N in one simulation, rate=0.5, list_num=8')
#添加注释 参数名xy：箭头注释中箭头所在位置，参数名xytext：注释文本所在位置，
#arrowprops在xy和xytext之间绘制箭头, shrink表示注释点与注释文本之间的图标距离

#plt.annotate('I\'m annotation', xy=(2,5), xytext=(2, 10),
#            arrowprops=dict(facecolor='black', shrink=0.01),
#            )

l1 = plt.legend([p1,p2,p3], \
                ["SCL_decode", "SCL_decode2", "fast_SCL_decode"], \
                loc='upper left')
#添加图例

#第3步：显示图形
plt.show()
