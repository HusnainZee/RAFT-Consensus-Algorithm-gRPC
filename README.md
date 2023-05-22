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

## Node Initialization:

Upon starting, each node process is provided with command-line arguments specifying its Node ID, Node status, and Term number.
Two processes are started as Candidates (Candidate 1 and Candidate 2) with Term numbers 9 and 15, respectively.
Three processes are started as Followers (Follower 1, Follower 2, and Follower 3) with Term numbers 10 and 7, respectively.

## Node Communication:

Nodes communicate with each other using RPC messages.
Each message contains the Node ID, Node status, Term number, and any additional information.
Whenever a message is sent or received, the Term number is incremented by 1.
Nodes maintain log files that record the contents of sent and received messages along with the corresponding Term number.

## Sending "Hello" Messages:

Once the node processes are alive, they send a "hello" message to every other node.
These messages serve as a basic communication check between nodes.
Each "hello" message contains the sender's Node ID, Node status, Term number, and any additional information.

## Requesting Votes as a Candidate:

Candidate processes wait for a random interval before sending a request for votes to all other nodes.
The vote request message includes the Candidate's Term number and the name of its log file.
Upon sending the request, the Candidate process increments its Term number by 1.
The vote request aims to gather votes from other nodes to become the leader.

## Voting Process:

When a node receives a vote request, it checks its own state and Term number before voting.
If the node has already voted for another candidate (hasVoted is true), it votes "NO" with its own Term number and Node ID.
If the node has not voted (hasVoted is false), it compares the Candidate's Term number with its own.
If the Candidate's Term number is lower, indicating outdated information, the node votes "NO" with its own Term number and Node ID.
If the Candidate's Term number is equal or higher, the node votes "YES" with its own Term number and Node ID.

## Candidate Processing Votes:

When a Candidate receives votes from other nodes, it processes the responses.
If any vote is "NO," the Candidate checks the corresponding Term number against its own.
If the Term number is not less, the Candidate updates its status to Follower, accepting that it is not up to date.
If a vote is "YES," the Node ID is added to the set of nodes that have voted "YES."
If the set size reaches (N/2 + 1), where N is the total number of nodes, the Candidate changes its status to Leader.
The Candidate then sends a message to all nodes, notifying them of its new status.

## Leader Election and Consensus:

Once a Candidate becomes a Leader, it initiates the leader election process.
The Leader sends a message to all nodes, announcing its new status as the Leader.
From this point on, the Leader coordinates the consensus process, replicating log entries and maintaining system consistency.
System Termination and Log Files:

After sending the initial "hello" messages, the node processes terminate.
Each node maintains a log file that records the contents of messages sent and received along with their corresponding Term numbers.
The log files can be accessed and read after the processes have terminated.
