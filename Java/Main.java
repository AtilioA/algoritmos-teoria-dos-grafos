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
    Map<Integer, ArrayList<Integer>> vertices = new HashMap<Integer, ArrayList<Integer>>();
    int nVertices;
    List<Boolean> visited;

    public Graph(int nVertices) {
        this.nVertices = nVertices;
        for (int i = 0; i < nVertices; i++) {
            // System.out.println("Initializing " + i + " vertex's adjacency list");
            this.vertices.computeIfAbsent(i, k -> new ArrayList<Integer>()).add(null);
            this.vertices.get(i).remove(null); // Unbelievable workarounds
        }
    }

    public void addConnection(int u, int v){
        this.vertices.get(u - 1).add(v - 1);
        this.vertices.get(v - 1).add(u - 1);
    }
}

public class Main {
    public static void main(String[] args) {
        // Testing HashMap to store adjacency vertices
        Map<Integer, List<Integer>> dictionary = new HashMap<Integer, List<Integer>>();
        dictionary.computeIfAbsent(10, k -> new ArrayList<>()).add(5);
        dictionary.computeIfAbsent(10, k -> new ArrayList<>()).add(666);
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
        graph = new Graph(5);

        for (int i = 0; i < graph.nVertices; i++) {
            System.out.println("Vertices adjacent to vertex " + i + ": " + graph.vertices.get(i));
        }

        System.out.println("Connecting vertices:");
        graph.addConnection(2, 1);
        graph.addConnection(1, 3);
        graph.addConnection(3, 2);
        graph.addConnection(1, 4);
        graph.addConnection(4, 5);

        for (int i = 0; i < graph.nVertices; i++) {
            System.out.println("Vertices adjacent to vertex " + i + ": " + graph.vertices.get(i));
        }
    }
}
