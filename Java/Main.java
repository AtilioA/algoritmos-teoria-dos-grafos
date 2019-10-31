import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.HashMap;
// import java.util.Scanner;

class Vertex {
    int id;
    int distance;
    boolean visited;
    ArrayList<Integer> adjacency;

    public Vertex(int id, ArrayList<Integer> adjacency) {
        this.distance = Integer.MAX_VALUE; // "Infinite" value to initialize distances
        this.id = id;
        this.adjacency = adjacency;
        this.visited = false;
    }

    public Vertex(int id) {
        this.distance = Integer.MAX_VALUE;
        this.id = id;
        this.adjacency = new ArrayList<Integer>();
        this.visited = false;
    }

    public int getID() {
        return id;
    }

    public int getDistance() {
        return distance;
    }

    public void setID(int id) {
        this.id = id;
    }

    public void setDistance(int dist) {
        this.distance = dist;
    }

    public ArrayList<Integer> getAdjacency() {
        return adjacency;
    }

    public void setAdjacency(ArrayList<Integer> adjacency) {
        this.adjacency = adjacency;
    }

    public boolean isVisited() {
        return visited;
    }

    public void setVisited(boolean visited) {
        this.visited = visited;
    }
}

class Edge {
    int originVertex, destinationVertex;

    public Edge(int originVertex, int destinationVertex) {
        super();
        this.originVertex = originVertex;
        this.destinationVertex = destinationVertex;
    }

    public int getOriginVertex() {
        return originVertex;
    }

    public void setOriginVertex(int originVertex) {
        this.originVertex = originVertex;
    }

    public int getDestinationVertex() {
        return destinationVertex;
    }

    public void setDestinationVertex(int destinationVertex) {
        this.destinationVertex = destinationVertex;
    }

}

class Graph {
    ArrayList<Vertex> vertices;

    public Graph() {
        this.vertices = new ArrayList<Vertex>();
    }

    public Graph(ArrayList<Vertex> vertices) {
        super();
        this.vertices = vertices;
    }

    public ArrayList<Vertex> getVertices() {
        return vertices;
    }

    public void setVertices(ArrayList<Vertex> vertices) {
        this.vertices = vertices;
    }

    public void addConnection(int u, int v){
        this.vertices.get(u - 1).adjacency.add(v);
        this.vertices.get(v - 1).adjacency.add(u);
    }
}

public class Main {
    public static void main(String[] args) {
        // Testing HashMap to store adjacency vertices
        Map<Integer, List<Integer>> dictionary = new HashMap<Integer, List<Integer>>();
        dictionary.computeIfAbsent(10, k -> new ArrayList<>()).add(5);
        dictionary.computeIfAbsent(10, k -> new ArrayList<>()).add(3);
        dictionary.computeIfAbsent(10, k -> new ArrayList<>()).add(2);
        dictionary.computeIfAbsent(10, k -> new ArrayList<>()).add(1);
        System.out.println("Vertices adjacent to vertex 10: " + dictionary.get(10));

        Vertex v1;
        v1 = new Vertex(1);
        Vertex v2;
        v2 = new Vertex(2);
        Vertex v3;
        v3 = new Vertex(3);
        ArrayList<Vertex> vertices = new ArrayList<Vertex>(3);
        vertices.add(v1);
        vertices.add(v2);
        vertices.add(v3);

        System.out.println("\nVertices infos:\n");
        for (int i = 0; i < vertices.size(); i++) {
            System.out.println(vertices.get(i).getID() + ", connected to " + vertices.get(i).getAdjacency());
        }

        System.out.println("\nCreating undirected graph and adding connections:");
        Graph graph;
        graph = new Graph(vertices);
        graph.addConnection(1, 3);
        graph.addConnection(2, 3);

        for (int i = 0; i < graph.getVertices().size(); i++) {
            System.out.println(graph.getVertices().get(i).getID() + ", connected to " + graph.getVertices().get(i).getAdjacency());
        }
    }
}
