import osmium
from math import radians, sin, cos, sqrt, atan2
from collections import defaultdict

class OSMHandler(osmium.SimpleHandler):
    def __init__(self):
        osmium.SimpleHandler.__init__(self)
        self.num_nodes = 0
        self.node_coords = {}
        self.node_mapping = {}
        self.adjacency_list = defaultdict(list)

    def node(self, n):
        self.node_mapping[n.id] = self.num_nodes
        self.node_coords[self.num_nodes] = (n.location.lat, n.location.lon)
        self.num_nodes += 1

    def way(self, w):
        node_refs = [self.node_mapping[node.ref] for node in w.nodes]
        for i in range(len(node_refs) - 1):
            source_node = node_refs[i]
            target_node = node_refs[i + 1]
            self.adjacency_list[source_node].append(target_node)

def haversine(lat1, lon1, lat2, lon2):
    R = 6371000  # Радиус Земли в метрах
    phi1 = radians(lat1)
    phi2 = radians(lat2)
    delta_phi = radians(lat2 - lat1)
    delta_lambda = radians(lon2 - lon1)
    
    a = (sin(delta_phi / 2) ** 2 +
         cos(phi1) * cos(phi2) * sin(delta_lambda / 2) ** 2)
    c = 2 * atan2(sqrt(a), sqrt(1 - a))
    
    return R * c

file_path = "/home/unik_um/AStar/datasets/filtered_belarus.osm"

handler = OSMHandler()
handler.apply_file(file_path)

with open("/home/unik_um/AStar/graph/graphbel.txt", "w") as file:
    file.write(str(handler.num_nodes) + "\n")

    for node, neighbors in sorted(handler.adjacency_list.items()):
        coords1_lat, coords1_lon = handler.node_coords[node]

        for neighbor in neighbors:
            coords2_lat, coords2_lon = handler.node_coords[neighbor]
            distance = haversine(coords1_lat, coords1_lon, coords2_lat, coords2_lon) ## !!!
            file.write(f"{node} {neighbor} {distance}\n")

with open("/home/unik_um/AStar/graph/coordsbel.txt", "w") as file:
    for node_id, coords in sorted(handler.node_coords.items()):
        lat, lon = coords
        file.write(f"{node_id} {lat} {lon}\n")
