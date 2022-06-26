import matplotlib.pyplot as plt

#1 基础绘图
#第1步：定义x和y坐标轴上的点   x坐标轴上点的数值
N=[128, 256, 512, 1024, 2048, 4096]
#y坐标轴上点的数值
generate_random_u=[3.600000e-05, 2.600000e-05, 4.800000e-05, 9.500000e-05, 1.870000e-04, 3.720000e-04]
encode=[2.200000e-05, 4.800000e-05, 1.030000e-04, 2.290000e-04, 4.790000e-04, 1.026000e-03]
pass_channel=[4.000000e-05, 7.600000e-05, 1.490000e-04, 2.930000e-04, 5.830000e-04, 1.159000e-03]
SC_deocde=[3.230000e-04, 7.330000e-04, 1.641000e-03, 3.625000e-03, 7.956000e-03, 1.730100e-02]
fast_SC_decode=[1.590000e-04, 4.030000e-04, 8.700000e-04, 1.845000e-03, 4.065000e-03, 8.821000e-03]
SCL_decode=[2.790000e-03, 6.808000e-03, 1.497200e-02, 3.323900e-02, 7.352400e-02, 1.626640e-01]

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

p1,=plt.plot(N,generate_random_u,marker='o')
p2,=plt.plot(N,encode,marker='o')
p3,=plt.plot(N,pass_channel,marker='o')
p4,=plt.plot(N,SC_deocde,marker='o')
p5,=plt.plot(N,fast_SC_decode,marker='o')
p6,=plt.plot(N,SCL_decode,marker='o')
'''
axis：坐标轴范围
语法为axis[xmin, xmax, ymin, ymax]，
也就是axis[x轴最小值, x轴最大值, y轴最小值, y轴最大值]
'''
#plt.axis([0, 6, 0, 20])


#对数坐标
plt.xscale("log",base=2)
plt.yscale("log")

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
plt.title('time consume verse N in one simulation, rate=0.5, list_num=8')
#添加注释 参数名xy：箭头注释中箭头所在位置，参数名xytext：注释文本所在位置，
#arrowprops在xy和xytext之间绘制箭头, shrink表示注释点与注释文本之间的图标距离

#plt.annotate('I\'m annotation', xy=(2,5), xytext=(2, 10),
#            arrowprops=dict(facecolor='black', shrink=0.01),
#            )

#添加图例
l1 = plt.legend([p6,p4,p5,p3,p2,p1], \
                ["SCL_decode", "SC_deocde", "fast_SC_decode", \
                 "pass_channel", "encode", "generate_random_u"], \
                loc='upper left')

#第3步：显示图形
plt.show()
