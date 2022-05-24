import random
import numpy as np
import networkx as nx
import graph as m7
import matplotlib.pyplot as plt

n = 5

C = [   [21,12, 6, 8, 3],
        [10, 6,11,16, 9],
        [ 5, 3,13, 7, 6],
        [ 6, 8, 4, 8, 4],
        [ 1, 2, 1, 3, 5]   ]
C1 = list()
C2 = list()
Cx = list()
min_row_elements = []
# Заполнение матриц
for i in range(n):
    #C.append([random.randint(10, 30) for j in range(n)])
    C1.append([0*n]*n)
    C2.append([0*n]*n)
    Cx.append(['.'] * n)

def create_graph_x(C):
    # G и Gx - экземпляры одного и того же графа
    # Gx - граф для отображения
    # G - граф для вычислений
    ## Построение двудольного оргграфа
    Gx = nx.DiGraph()

    for i in range(n):
        for j in range(n):
            if C2[i][j] == 0:
                Gx.add_edge("s" + str(i + 1), "t" + str(j + 1), capacity=1.0)

    for i in range(1, n + 1):
        Gx.add_edge("s", "s" + str(i), capacity=1.0)
        Gx.add_edge("t" + str(i), "t", capacity=1.0)
    return Gx

def create_graph(C2):
    G = m7.Graph()

    G.add_node('s')
    G.add_node('t')
    G.set_source('s')
    G.set_target('t')

    for i in range(1, n + 1):
        G.add_node('s' + str(i))
        G.add_node('t' + str(i))

    for i in range(1, n + 1):
        G.add_edge('s', 's' + str(i), 1)
        G.add_edge('t' + str(i), 't', 1)

    for i in range(n):
        for j in range(n):
            if C2[i][j] == 0:
                G.add_edge('s' + str(i + 1), 't' + str(j + 1), 1)
    return G

def set_node_colors(Gx):
    node_colors = ['#D90000' if 's' in node else '#195A63' for node in Gx.nodes]
    return node_colors

def set_edge_colors(Gx):
    edge_colors = ['#373737' if 's' in edge else '#373737' for edge in Gx.nodes]
    return edge_colors

def view_graph(Gx):
    ## Визуализация графа
    plt.figure(figsize=(4, 4))
    nx.draw(Gx, node_color=set_node_colors(Gx), edge_color=set_edge_colors(Gx), arrows=True, with_labels=True);
    plt.show()
    plt.savefig("xgraph.png")

def matrix_reduction(C,C1,C2):
    ### Выполняем операцию приведения матрицы

    view_array(C, "C")

    for i in range(len(C)):
        min_row_elements.append(min(C[i]))
    print("Константы приведения по строкам:", min_row_elements)

    # Заполнение С1
    for i in range(n):
        for j in range(n):
            C1[i][j] = C[i][j] - min_row_elements[i]

    view_array(C1, "C1")

    min_col_elements = [min(C1[i][j] for i in range(n)) for j in range(n)]
    print("Константы приведения по столбцам:", min_col_elements)

    # Заполнение С2
    for i in range(n):
        for j in range(n):
            C2[j][i] = C1[j][i] - min_col_elements[i]

    view_array(C2, "C2")

def view_array(array, name):
    print("\n\t\t{0}:".format(name))
    for i in range(len(array)):
        print("[ ", end="")
        for j in range(len(array[i])):
            print("{0:<2}".format(array[i][j]), end=' ')
        print("]")
    print()


###########################
###########################


matrix_reduction(C,C1,C2)


Gx = create_graph_x(C2)
G = create_graph(C2)


result = G.ford_fulkerson_alg_komandina()

max_flow = result[0]
auxiliary_vertices = result[1]

print('---------- Максимальный поток =', max_flow,'----------\n')

while max_flow < n:

    C3 = G.c3_reduction(C2, Cx, auxiliary_vertices,n)

    view_array(Cx,'Cx')
    view_array(C3,'C3')
    view_graph(Gx)

    Gx = create_graph_x(C3)
    G = create_graph(C2)
    result = G.ford_fulkerson_alg_komandina()
    max_flow = result[0]
    print('---------- Максимальный поток =', max_flow,'----------\n')













#######################
##############    NOTES
## Нахождение максимального потока в сети
#max_flow = nx.flow.maximum_flow(Gx, "s", "t")
#print(max_flow)