import math
import matplotlib.pyplot as plt
import collections
from openpyxl import Workbook

STYLES = [
    ('lightsteelblue', 's'),
    ('royalblue', 'o'),
    ('tomato', 'x'),
    ('limegreen', 'h'),
    ('hotpink', 'v'),
    ('orange', '^'),
]

PLOT_SIZE = (20, 10)
DPI=1000

def get_x_y_data(graph_data):
    x = []
    y = []
    for i in graph_data:
        t = list(map(float, i.split()))
        x.append(t[0])
        y.append(t[1])
    
    return x, y


with open('config.ini') as config:
    names = config.readline().split()
    opts = config.readline().split()
    sizes = config.readline().split()

for name in names:
    for opt in opts:
        wb_path_save = f'./postproc_data/{name}_{opt}.xlsx'
        graph = open(f'./postproc_data/{name}_{opt}.txt', 'w')

        wb = Workbook()
        ws = wb.active
        ws.append(("Размер массива", "Время выполнения ", 'Величина относительной стандартной ошибки среднего'))


        for size in sizes:
            params = open(f'./preproc_data/{name}_{opt}_{size}.txt').readlines()

            mean = params[0].strip()
            median = params[1].strip()
            maxx = params[2].strip()
            minn = params[3].strip()
            per_25 = params[4].strip()
            per_75 = params[5].strip()
            variance = float(params[6].strip())

            s = math.sqrt(variance)
            stderr = s/math.sqrt(int(size))
            try:
                rse = stderr/float(mean) * 100
            except ZeroDivisionError:
                rse = 0.0

            ws.append((size, mean, str(rse)))

            graph.write(f'{size} {mean}\n')

            
        wb.save(wb_path_save)
        wb.close()

        graph.close()

try:
    plt.figure(figsize=PLOT_SIZE)
    plt.grid(True)
    plt.xlabel("Размер матрицы")
    plt.ylabel("Время")
    i = 0
    for name in names:
        for opt in opts:
            if opt == 'O2':
                continue
            graph = open(f'./postproc_data/{name}_{opt}.txt', 'r').readlines()
            x, y = get_x_y_data(graph)
            plt.xticks(x, sizes, rotation=45, ha='right')
            plt.plot(x, y, color=STYLES[i][0], marker=STYLES[i][1], label=f'{name} {opt}')
            i += 1
    plt.legend()
    plt.savefig('linear.svg', dpi=DPI)
    plt.close()
except:
    pass

