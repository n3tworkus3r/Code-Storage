import math

class Node:
    name = ''
    source = False
    target = False

    tagged = False
    viewed = False
    tag = []

    neightbors = []

    def __init__(self, name, source=False, target=False):
        self.name = name
        self.source = source
        self.target = target

    def __repr__(self):
        return "%s" % (self.name)

    def set_tag(self,predecessor,capacity):
        self.tag = [predecessor,capacity]
        viewed = True
        tagged = True
        pass

    def get_tag(self):
        return self.tag



class Edge:
    u = ''
    v = ''
    capacity = 0
    flow = 0

    def __init__(self, u, v, capacity,direction):

        self.u = Node(u).name
        self.v = Node(v).name
        self.capacity = capacity
        self.flow = 0
        self.direction = '+'
        #self.reverse_edge = None



        #self.v.tag = ['u', capacity]
    def __repr__(self):
        return "%s->%s" % (self.u, self.v)

class Graph:
    def __init__(self):
        self.nodes = []
        self.network = {}

    def get_source(self):
        for node in self.nodes:
            if node.source == True:
                return node
        return None

    def set_source(self, new_source):
        for node in self.nodes:
            if node.source == True:
                node.source = False
        for node in self.nodes:
            if node.name == new_source:
                node.source = True
                return node
        return None

    def get_target(self):
        for node in self.nodes:
            if node.target == True:
                return node
        return None

    def set_target(self, new_target):
        for node in self.nodes:
            if node.target == True:
                node.target = False
        for node in self.nodes:
            if node.name == new_target:
                node.target = True
                return node
        return None

    def get_node(self, name):
        for node in self.nodes:
            if name == node.name:
                return node

    def node_in_network(self, name):
        for node in self.nodes:
            if node.name == name:
                return True
        return False

    def add_node(self, name, source=False, target=False):
        if source == True and target == True:
            return "Узел не может быть источником и стоком"
        if self.node_in_network(name):
            return "Узел уже существует"
        if source == True:
            if self.get_source() != None:
                return "Исток уже существует"
        if target == True:
            if self.get_target() != None:
                return "Сток уже существует"
        new_node = Node(name, source, target)
        self.nodes.append(new_node)
        self.network[new_node.name] = []

    def get_neightbors(self,node_name):
        neightbor_list = []
        node = self.get_node(node_name)
        for edge in self.network[node.name]:
            for node in self.nodes:
                if edge.v == node.name:
                    neightbor_list.append(node)
        return neightbor_list

    def add_edge(self, u, v, capacity):
        if u == v:
            return "Нельзя добавить одинаковые исток и сток"
        if self.node_in_network(u) == False:
            return "Вершина 'u' ещё не добавлена"
        if self.node_in_network(v) == False:
            return "Вершина 'v' ещё не добавлена"
        new_edge = Edge(u, v, capacity,'+')
        node = self.get_node(u)
        self.network[node.name].append(new_edge)

        new_edge = Edge(v, u, capacity, '-')
        node = self.get_node(v)
        self.network[node.name].append(new_edge)

    def view_network(self):
        routes = self.network.values()
        for i in routes:
            print(i)

    def view_nodes(self):
        for i in self.nodes:
            print(i)

    def get_edge(self, u,v):
        for edge in self.network[u]:
            if edge.u == u and edge.v == v:
                return edge

    def tag_a_neighbor(self, u, not_tagged):
        #neightbor_list = self.get_neightbors(u.name)
        tagged_list = []
        # Выбираем смежный узел
        for v in not_tagged:
            edge = self.get_edge(u.name, v.name)
            if edge.flow != edge.capacity:
                if edge.flow < edge.capacity:
                    v.tag = [u.name,min(u.tag[1], edge.capacity - edge.flow),'+']
                    v.tagged = True
                    if v not in tagged_list:
                        tagged_list.append(v)
                    print(v.name, '=', v.get_tag())
                elif edge.flow > 0:
                    v.tag = [u.name, min(u.tag[1], edge.flow), '-']
                    v.tagged = True
                    if v not in tagged_list:
                        tagged_list.append(v)
                    print(v.name, '=', v.get_tag())
        if v.name == 't':
            return tagged_list + ['t']

        not_tagged.clear()

        return tagged_list


    def viewing_node(self, source):
        not_tagged = []
        print("\n\tПросматриваем вершину {0}:".format(source.name))
        neighbor_list = self.get_neightbors(source.name)
        for node in neighbor_list:
            if node.tagged == False:
                not_tagged.append(node)
                edge = self.get_edge(source.name, node.name)
                print(node.name,'[{0}/{1}] - не помечена'.format(edge.capacity,edge.flow))
        return not_tagged


    def increasing_chain(self, source, target):
        v = Node(target.name)
        u = Node('x')

        chain = []
        while v.name != source.name:
            for node in self.nodes:
                if node.name == target.name:
                    v = node
                    break

            for node in self.nodes:
                if node.name == target.tag[0]:
                    u = node
                    break
            edge = self.get_edge(u.name, v.name)

            if v.tag[2] == '+':
                edge.flow = v.tag[1]
                chain.append(edge)

            v = u
            target = v

        chain.reverse()
        return chain

    def c3_reduction(self, C2, Cx, auxiliary_vertices, n):

        t_untagged = []
        s_tagged = []
        t_tagged = []

        for node in auxiliary_vertices:
            if 's' in node.name:
                s_tagged.append(node.name)
        s_tagged.pop(0)
        print('Множество s помеченных ->', s_tagged)

        for node in self.nodes:
            if 't' in node.name and (node not in auxiliary_vertices):
                t_untagged.append(node.name)
        t_untagged.pop(0)
        print('Множество t непомеченных ->', t_untagged)

        for node in self.nodes:
            if 't' in node.name and (node.name not in t_untagged):
                t_tagged.append(node.name)
        t_tagged.pop(0)

        for i in range(len(t_tagged)):
            t_tagged[i] = t_tagged[i][1:]

        for i in range(len(s_tagged)):
            s_tagged[i] = s_tagged[i][1:]

        for i in range(len(t_untagged)):
            t_untagged[i] = t_untagged[i][1:]

        temp_list = []

        for i in s_tagged:
            for j in t_untagged:
                Cx[int(i) - 1][int(j) - 1] = C2[int(i) - 1][int(j) - 1]
                temp_list.append(C2[int(i) - 1][int(j) - 1])

        #self.view_array(Cx, 'Cx')

        min_value = min(temp_list)
        print('Минимальный элемент в матрице Сх ->', min_value)

        C3 = C2.copy()
        for i in range(n):
            for j in range(n):
                if type(Cx[i][j]) == int:
                    C3[i][j] = C2[i][j] - min_value

        for i in t_tagged:
            for j in range(n):
                if C3[j][int(i) - 1] != 0:
                    C3[j][int(i) - 1] += min_value

        return C3

    def ford_fulkerson_algorithm(self):

        i = 1
        chain_list = []

        while True:
            print('\t\t\tИТЕРАЦИЯ', str(i)+':\n')

            i += 1
            tagged_list = []
            not_tagged = []
            auxiliary_vertices = []
            u = self.get_source()
            target = self.get_target()


            # 0) Все вершины не помечены
            for node in self.nodes:
                node.tagged = False
                node.tagged = False

            # 1) Вершина s получает метку ['∅', '∞']
            u.tag = ['∅', math.inf]
            u.tagged = True
            tagged_list.append(u)
            print(self.get_source() ,"-->",u.get_tag())


            route = []
            while len(tagged_list) > 0:
                neighbor_list = self.get_neightbors(u.name)

                # 2) Просматриваем вершину:
                not_tagged = self.viewing_node(u)

                # 3) Помечаем смежные вершины:
                if len(not_tagged) > 0:
                    print("\n\tПомечаем вершины для {0}".format(u.name))
                    tagged_list += self.tag_a_neighbor(u,not_tagged)

                # Если помечена вершина 3, переходим к шагу 2 (строим увеличивающую цель)
                    if 't' in tagged_list:
                        print("\n\n\t\tЭТАП 2")
                        tagged_list.remove('t')
                        chain = self.increasing_chain(self.get_source(),tagged_list[-1])
                        chain_list.append(chain)
                        print("Увеличивающая цепь -> ",chain,'\n\n')
                        break


                # 4) Помечаем просмотренной вершину, переходим к другой
                u.viewed = True
                tagged_list.remove(u)
                auxiliary_vertices.append(u)

                #5) Если вершина просмотрена и нет помеченных
                if len(tagged_list) == 0 and u.viewed == True:
                    print("\n\tВершина {0} просмотрена\n".format(u))
                    max_flow = 0
                    source = self.get_source()

                    neighbor_list = self.get_neightbors(source.name)
                    for node in neighbor_list:
                        edge = self.get_edge(source.name, node.name)
                        max_flow += edge.flow

                    return [max_flow,auxiliary_vertices,chain_list]


                print("\n\tВершина {0} просмотрена\n".format(u))
                u = tagged_list[0]

                print('##################################')

            ##########################################################
            ##########################################################
            ##########################################################

            def get_route(self, source, target, route):
                if source == target:
                    return route
                for edge in self.network[source]:
                    residual = edge.capacity - edge.flow
                    if residual > 0 and not (edge, residual) in route:
                        result = self.get_route(edge.v, target, route + [(edge, residual)])
                        if result != None:
                            return result

            def route(self, source, target):
                while source.name != target.name:
                    node = self.tag_a_neighbor(source)
                    source = node

            def calculate_max_flow(self):
                source = self.get_source()
                target = self.get_target()
                if source == None or target == None:
                    return "Network does not have source and target"
                path = self.get_route(source.name, target.name, [])
                while path != None:
                    flow = min(edge[1] for edge in path)
                    for edge, res in path:
                        edge.flow += flow
                        edge.reverse_edge.flow -= flow
                    path = self.get_route(source.name, target.name, [])
                return sum(edge.flow for edge in self.network[source.name])

























