# Pipe Flow Network Simulator and Calculator

This program simulates an in-depth model of pipe flow networks, allowing users to analyze and visualize fluid flow through interconnected pipes. This README includes an introduction to pipe flow networks, an explanation of the Ford-Fulkerson algorithm, and instructions for setup and usage.

## Introduction to Pipe Flow Networks and Maximum Flow

Pipe flow networks are systems where interconnected pipes facilitate the movement of fluids, like water or oil, from a source to one or more destinations. These networks are widely used in engineering disciplines to model real-life systems, such as water supply systems, oil pipelines, and even HVAC systems in buildings. Each pipe in the network has a specific capacity, meaning there is a limit to the volume or flow rate it can handle. 

One key challenge in these systems is determining the **maximum flow** — the highest amount of fluid that can be transported from the source to the destination without exceeding the capacities of individual pipes. This is critical for optimizing the design of a network to avoid bottlenecks, ensure efficient resource distribution, and meet demand.

The maximum flow calculation considers not only the capacity of each pipe but also the configuration of the network, including parallel paths that can distribute the load. Calculating the maximum flow provides insight into the network’s efficiency and highlights potential points where capacity might be improved.

## About the Ford-Fulkerson Algorithm

The Ford-Fulkerson algorithm is a foundational method for solving the maximum flow problem in a network. In a pipe flow network, it helps determine the maximum flow from a designated source node to a sink (or destination) node. Ford-Fulkerson identifies **augmenting paths**, which are routes where more flow can be added without exceeding pipe capacities. It iteratively finds these paths, adjusting the flow along each one until no more augmenting paths can be identified. At this point, the algorithm provides the maximum flow value.

This algorithm is efficient, adaptable, and well-suited for flow simulations, making it an ideal choice for our pipe flow network model.

## Setup Instructions

### Prerequisites

- **Operating System**: Linux (recommended for compatibility)
- **Compiler**: A C++ compiler, such as `g++`
  
### Installation and Compilation

1. **Clone the Repository**: First, download all program files to your local machine.
   ```bash
   git clone <repository-url>
   cd <repository-directory>

2. **Compile the Program**: Use a C++ compiler to compile the main.cpp file.
   ```bash
   g++ main.cpp -o pipe_flow_simulator

3. **Run the Program**: Execute the compiled binary to start the simulation.
   ```bash
   ./pipe_flow_simulator

## Configuring Input Files

The program reads flow network configurations from input `.txt` files. Two sample files, `network1.txt` and `network2.txt`, are provided to demonstrate the format. Each file represents a network of pipes where fluid flows from a source (`s`) to a sink (`t`), passing through various nodes. 

### Input File Format

Each line in the file describes a single pipe in the network using the following structure:

node1,node2,max_flow

-**node1:** The starting node of the pipe (edge) in the network.

-**node2:** The ending node of the pipe.

-**max_flow:** The maximum flow capacity of the pipe, representing the maximum volume of fluid it can transport.

## Special Nodes:

**"s"** (source): Represents the starting point of the network where flow begins.

**"t"** (sink): Represents the endpoint where flow exits the network.

## Example Input File
Below is an example of a .txt input file:

```bash
s,v1,16
s,v2,13
v1,v3,12
v2,v1,4
v2,v4,14
v3,v2,9
v3,t,20
v4,v3,7
v4,t,4
```

## Explanation
In this example:

s,v1,16 indicates a pipe from the source s to node v1 with a maximum flow capacity of 16.
s,v2,13 indicates a pipe from the source s to node v2 with a maximum flow capacity of 13.
v1,v3,12 indicates a pipe from node v1 to node v3 with a maximum flow capacity of 12.
Each line builds a part of the network's structure, defining both the connections between nodes and the flow limits of each pipe. The program will use this data to calculate the maximum flow from the source (s) to the sink (t).

## Using Custom Input Files
To use a custom configuration:

Edit either one of the given network.txt files with lines following the format shown above.
Ensure each connection includes a defined max_flow.
Save the file in the same directory as the program files, and the program will run and calculate your new flow network automatically.
