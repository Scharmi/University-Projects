class weighed_directed_graph:
    def __init__(self):
        self.edges = dict()
        self.vertices = set()
        
    def add_vertex(self, vertex):
        if vertex not in self.vertices:
            self.edges[vertex] = set()
            self.vertices.add(vertex)
            
    def add_edge(self, vertex_1, vertex_2, weight):
        if vertex_1 in self.vertices and vertex_2 in self.vertices:
            self.edges[vertex_1].add((vertex_2, weight))
    def remove_edge(self, vertex_1, vertex_2):
        if vertex_1 in self.vertices and vertex_2 in self.vertices:
            self.edges[vertex_1].remove(vertex_2)
    def remove_vertex(self, vertex):
        if vertex in self.vertices:
            self.vertices.remove(vertex)
            self.edges.pop(vertex)
            for i in self.edges:
                for j in self.edges[i]:
                    if j[0] == vertex:
                        self.edges[i].remove(j)
    def find_shortest_path(self, vertex_1, vertex_2):
        if vertex_1 in self.vertices and vertex_2 in self.vertices:
            visited = set()
            queue = [(vertex_1, 0)]
            while queue:
                (vertex, cost) = queue.pop(0)
                if vertex not in visited:
                    visited.add(vertex)
                    if vertex == vertex_2:
                        return cost
                    for (neighbour, weight) in self.edges[vertex]:
                        if neighbour not in visited:
                            queue.append((neighbour, cost + weight))
            return float("inf")
        else:
            return float("inf")

    

    

    
    
    