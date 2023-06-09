###

<p align="center">
  <img src="https://github.com/HusnainZee/RAFT-Consensus-Algorithm-gRPC/blob/main/Visualization.png" alt="RAFT Visualization" /> 
</p>

# RAFT-Consensus-Algorithm-gRPC
This project is the implementation of the Raft Consensus Algorithm in the Distributed Systems using gRPC Library in C++.

## Overview
The Raft algorithm is a consensus algorithm designed for distributed systems to ensure fault tolerance and consistency. It is used to elect a leader among a group of nodes. The algorithm provides safety guarantees, including leader election and node status changes from Candidate to Leader or from Candidate to Follower. It is commonly used in distributed databases and replicated state machines.

## Project Details
### System Overview:

- The system consists of 5 node processes, each representing a distinct node in the distributed system.
- Communication between nodes is done via Remote Procedure Calls (RPC) using a configuration file.
- Each node has a unique Node ID, Node status (Candidate or Follower), and Term number.
- Node processes maintain log files to record messages sent and received.
- Terms 'Node' and 'Process' are used interchangeably.

### Node Initialization:

- Upon starting, each node process is provided with command-line arguments specifying its Node ID, Node status, and Term number.
- Processes can be started as either Candidates or Followers with different Term numbers.

### Node Communication:

- Nodes communicate with each other using RPC messages.
- Each message contains the Node ID, Node status, Term number, and some additional information.
- Whenever a message is sent or received, the Term number is incremented by 1.
- Nodes maintain log files that record the contents of sent and received messages along with the corresponding Term number.

### Sending Messages:

- Once the node processes are alive, they send messages to every other node.
- These messages serve as a basic communication check between nodes.
- Each message contains the sender's Node ID, Node status, Term number, and some additional information.

### Requesting Votes as a Candidate:

- Candidate processes wait for a random interval before sending a request for votes to all other nodes.
- The vote request message includes the Candidate's Term number and the name of its log file.
- Upon sending the request, the Candidate process increments its Term number by 1.
- The vote request aims to gather votes from other nodes to become the leader.
 
### Voting Process:

When a node receives a vote request, it checks its own state and Term number before voting.
- If the node has already voted for another candidate (hasVoted is true), it votes "NO" with its own Term number and Node ID.
- If the node has not voted (hasVoted is false), it compares the Candidate's Term number with its own.
- If the Candidate's Term number is lower, indicating outdated information, the node votes "NO" with its own Term number and Node ID.
- If the Candidate's Term number is equal or higher, the node votes "YES" with its own Term number and Node ID.

### Candidate Processing Votes:

When a Candidate receives votes from other nodes, it processes the responses.
- If any vote is "NO," the Candidate checks the corresponding Term number against its own.
- If the Term number is not less, the Candidate updates its status to Follower, accepting that it is not up to date.
- If a vote is "YES," the Node ID is added to the set of nodes that have voted "YES."
- If the set size reaches (N/2 + 1), where N is the total number of nodes, the Candidate changes its status to Leader.


### Leader Selection and its Acknowledgment:

- Once a Candidate becomes a Leader, it then sends a message to all nodes, notifying them of its new status as the Leader.
- The status of other Candidate processes are set to Follower to ensure there is a only one Leader.

### System Termination and Log Files:

- After receiving acknowledgments about the selection of Leader, the node processes terminate.
- Each node maintains a log file that records the contents of messages sent and received along with their corresponding Term numbers.
- The log files can be accessed and read after the processes have been terminated.

## Project Setup
- Install gRPC by following their offical documentation.
- Clone this repo in grpc/examples/cpp/
- Open the given directory in terminal and run the following commands:
  - $ mkdir -p cmake/build
  - $ pushd cmake/build
  - $ cmake -DCMAKE_PREFIX_PATH=$MY_INSTALL_DIR ../..
  - $ make -j 4
- After running the commands, you can execute the server.cc file by typing in the terminal: </br>
$ ./server [Node Id] [Follower/Candidate] [Term Number] [Port Address] [Message to be Sent] 
- You need to run these commands for each process in multiple terminals (max 5) in order to simulate the distributed environment.

