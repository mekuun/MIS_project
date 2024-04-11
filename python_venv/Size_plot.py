import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

def read_points(filename):
    points = []
    with open(filename, 'r') as f:
        for line in f:
            parts = line.strip().split(',')
            if len(parts) == 2:
                x, y = map(float, parts)
                if x < 20000:
                    points.append((y, x))
    return points

def plot_graph_and_points(points):
    # Создание массива значений x от 0 до 100
    x_values = np.linspace(0, 30, 400)

    # Разделение точек на координаты x и y
    x_points, y_points = zip(*points)

    # Добавление точек на график
    plt.scatter(x_points, y_points, color='red', label='Множества', s = 0.5)

    # Настройка графика
    plt.xlabel('x')
    plt.ylabel('y')
    plt.legend()


    plt.show()

# Основная часть программы
if __name__ == '__main__':
    points = read_points('output6.txt')  # Считывание точек из файла
    plot_graph_and_points(points)  # Построение графика и отображение то
