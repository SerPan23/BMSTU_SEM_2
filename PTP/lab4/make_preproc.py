import math
import statistics as stat

def percentile(data, q):
    data_sorted = sorted(data)
    
    index = math.ceil(q / 100 * len(data_sorted))

    return data_sorted[index - 1]

with open('config.ini') as config:
    names = config.readline().split()
    opts = config.readline().split()
    init_types = config.readline().split()
    sizes = config.readline().split()

for name in names:
    for opt in opts:
        for init_type in init_types:
            for size in sizes:
                data = [float(i) for i in open(f'./data/{name}_{opt}_{init_type}_{size}.txt').readlines()]
                with open(f'./preproc_data/{name}_{opt}_{init_type}_{size}.txt', 'w') as output:
                    m = stat.mean(data)
                    output.write(f"{m}\n")
                    output.write(f"{stat.median(data)}\n")
                    output.write(f"{max(data)}\n")
                    output.write(f"{min(data)}\n")
                    output.write(f"{percentile(data, 25)}\n")
                    output.write(f"{percentile(data, 75)}\n")
                    output.write(f"{stat.variance(data, m)}\n")
