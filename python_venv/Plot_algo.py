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
                if x < 25000: #ограничение на те результаты, которые лишком выбиваются из общей тенденции
                    points.append((y, x))
    return points

def plot_graph_and_points(points):
    # Создание массива значений x от 0 до 100
    x_values = np.linspace(0, 30, 400)

    # Вычисление y = x^ для каждого значения x
    y_values = x_values ** 3 / 4.5

    # Построение графика функции x^3
    plt.plot(x_values, y_values, label=' x^3 / 4.5')

    # Разделение точек на координаты x и y
    x_points, y_points = zip(*points)

    # Добавление точек на график
    plt.scatter(x_points, y_points, color='red', label='Точки из файла', s = 0.5)

    # Настройка графика
    plt.title('График кубической функции и точки из файла')
    plt.xlabel('x')
    plt.ylabel('y')
    plt.legend()


    plt.show()

# Основная часть программы
if __name__ == '__main__':
    points = read_points('output.txt')  # Считывание точек из файла
    plot_graph_and_points(points)  # Построение графика и отображение точек