#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include <memory>
#include <chrono>
#include <random>
#include <thread>

#include <cstdio>
#include <filesystem>

// LISTENING LIBRARIES
#include <grpcpp/grpcpp.h>

#ifdef BAZEL_BUILD
#include "node.grpc.pb.h"
#else
#include "node.grpc.pb.h"
#endif

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using RaftNodes::StringRequest;
using RaftNodes::StringReply;
using RaftNodes::StringVoteRequest;
using RaftNodes::StringVoteReply;
using RaftNodes::StringStatusUptateRequest;
using RaftNodes::StringStatusUptateReply;

using RaftNodes::MsgService;

//


using grpc::Channel;
using grpc::ClientContext;
using namespace std;


class Node
{
public:
   
    int id;
    string address;
    string status;
    int term;
    
    //
    bool hasVoted = false;
    string myVote = "";
    string filename = "";

};

Node newNode;

// SERVER IMPLEMENTATION - LISTENING


class GreeterServiceImpl final : public MsgService::Service 
{
  public:

    // RECEIVING MSG FROM CLIENT

    // ++ STRING REPLY IS THE RESPONSE MESSAGE SENT BACK AFTER RECEIVING MSG

    void checkAndWriteHeader(string filename, string header)
    {
        ifstream file(filename);
        bool fileExists = file.good();
        
        if (!fileExists) 
        {
            ofstream newFile(filename);
            newFile << header << endl;
            newFile.close();
        } 
        else 
        {
            bool headerFound = false;
            string line;
            for (int i = 0; i < 2 && getline(file, line); i++) 
            {
                if (line == header) 
                {
                    headerFound = true;
                    break;
                }
            }
            file.close();
            
            if (!headerFound) 
            {
                ofstream outFile(filename, ios::app);
                outFile << header << endl;
                outFile.close();
            }
        }   
    }
    
    Status sendRequest(ServerContext* context, const StringRequest* request, StringReply* reply) override 
    {

        cout.flush();
        
        newNode.term += 1;

        checkAndWriteHeader(newNode.filename, "Status\t\t\tId\t\tStatus\t\tterm\t\tmsg\t\tMyTerm");
        ofstream log_file(newNode.filename, ios::app);


        log_file << "RCVD FROM" << "\t\t" << request->nodeid() << "\t\t" << request->nodestatus() << "\t" << request->termnumber() << "\t\t" << request->message() << "\t\t" << newNode.term << "\n";


        // // INTERFACE

        cout << "\n\t\tRECEIVING \n";

        cout << "\nI GOT MSG: " << request->message();          
        cout << "\nSender Id: " << request->nodeid();           
        cout << "\nSender Term: " << request->termnumber();     
        cout << "\nSender Status: " << request->nodestatus();   
        cout << "\nMy Term: " << newNode.term  << "\n\n";       

        // Echo back the same message in the response
        
        reply->set_rcv_nodeid(request->nodeid());
        reply->set_rcv_nodestatus(request->nodestatus());
        reply->set_rcv_termnumber(request->termnumber());
        reply->set_rcv_message(request->message());

        return Status::OK;
    }   

    Status sendVoteRequest(ServerContext* context, const StringVoteRequest* request, StringVoteReply* reply) override 
    {

        cout.flush();

        cout << "\n\tRESPONDING TO VOTE REQUEST\n";
        cout << "\nCandid Term: " << request->termnumber() << endl;
        cout << "My Term: " << newNode.term << endl;
        cout << "Candid Filename: " << request->logname() << endl;

        if (newNode.hasVoted == true)
        {
            // sending back my details
            cout << "My Vote: No\n";
            
            reply->set_rcv_vote("no");
        }
        else if (newNode.hasVoted == false)
        {
            if (request->termnumber() >= newNode.term)
            {
                // sending back my details
                cout << "My Vote: Yes\n";

                reply->set_rcv_vote("yes");
            }
            else if (request->termnumber() < newNode.term)
            {
                // sending back my details
                cout << "My Vote: No\n";

                reply->set_rcv_vote("no");
            }
        }

        cout << "\n\n";
        reply->set_rcv_termnumber(newNode.term);
        reply->set_rcv_nodeid(newNode.id);

        return Status::OK;
    }   

    Status sendStatusUpdateRequest(ServerContext* context, const StringStatusUptateRequest* request, StringStatusUptateReply* reply) override 
    {

        cout.flush();
        cout << "ACKNOWLEDGED: " << request->status() << endl;
        reply->set_rcv_status(request->status());

        return Status::OK;
    }   
};

// STARTING SERVER
void listenForMessages(string nodeaddress) 
{
    string server_address(nodeaddress);
    GreeterServiceImpl service;

    
    ServerBuilder builder;
    // Listen on the given address without any authentication mechanism.
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    // Register "service" as the instance through which we'll communicate with
    // clients. In this case it corresponds to an *synchronous* service.
    builder.RegisterService(&service);
    // Finally assemble the server.
    unique_ptr<Server> server(builder.BuildAndStart());
    cout << "Server listening on " << server_address << endl;

    // Wait for the server to shutdown. Note that some other thread must be
    // responsible for shutting down the server for this call to ever return.
    server->Wait();
}


// LISTENING VOTE MSGS
void listenForVoteMessages(string nodeaddress) 
{

    // cout << "\nLISTENING FOR VOTE MESSAGES\n";

    string server_address(nodeaddress);
    GreeterServiceImpl service;

    ServerBuilder builder;
    // Listen on the given address without any authentication mechanism.
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    // Register "service" as the instance through which we'll communicate with
    // clients. In this case it corresponds to an *synchronous* service.
    builder.RegisterService(&service);
    // Finally assemble the server.
    unique_ptr<Server> server(builder.BuildAndStart());
    cout << "Server listening on " << server_address << " for Voting!" << endl;

    // Wait for the server to shutdown. Note that some other thread must be
    // responsible for shutting down the server for this call to ever return.

    while(true)
    {
        // cout << "VOTING DONE!\n";
        server->Wait();
    }
}




//  CLIENT IMPLEMENTATION - SENDING 


class GreeterClient 
{
    public:
    GreeterClient(shared_ptr<Channel> channel) : stub_(MsgService::NewStub(channel)) {}

    // Assembles the client's payload, sends it and presents the response back
    // from the server.

    // SENDING MSGS TO SERVER VIA StringRequest 
    // and RECEIVING RESPONSE VIA StringReply

    string sendRequestt(int nodeID, string nodeStatus, const string& message, string address) 
    {

        // Data we are sending to the server.
        StringRequest request;


        request.set_nodeid(nodeID);
        request.set_nodestatus(nodeStatus);
        request.set_termnumber(newNode.term);
        request.set_message(message);
        request.set_address(address);

        // Container for the data we expect from the server.
        StringReply replyy;

        // Context for the client. It could be used to convey extra information to
        // the server and/or tweak certain RPC behaviors.
        ClientContext context; 

        // The actual RPC.

        // ACTUAL SENDING MSG 

        Status status = stub_->sendRequest(&context, request, &replyy);

        // Act upon its status.
        if (status.ok()) 
        {
            return replyy.rcv_message(); 
        } 
        else 
        {
            string re = replyy.rcv_message()  + "Failed";
            return re;
        }
    }

    string sendVoteRequestt(int& termNumber, const string& logname, int& returnVoterId, int& returnVoterTerm) 
    {
        // Data we are sending to the server.
        StringVoteRequest request;

        request.set_termnumber(termNumber);
        request.set_logname(logname);

        // Container for the data we expect from the server.
        StringVoteReply replyy;

        // Context for the client. It could be used to convey extra information to
        // the server and/or tweak certain RPC behaviors.
        ClientContext context; 

        // The actual RPC.

        // ACTUAL SENDING MSG 
        Status status = stub_->sendVoteRequest(&context, request, &replyy);

        // Act upon its status.
        if (status.ok()) 
        {
            cout << "\nGot Response From id: " << replyy.rcv_nodeid() << endl ;
            cout << "Got Response From Term: " << replyy.rcv_termnumber() << endl ;
            cout << "My Term: " << newNode.term << endl;
            cout << "Got Vote: " << replyy.rcv_vote() << endl ;

            returnVoterId = replyy.rcv_nodeid();
            returnVoterTerm = replyy.rcv_termnumber();

            return replyy.rcv_vote(); 
        } 
        else 
        {
            cout << "\nGot Response From id: " << replyy.rcv_nodeid() << endl ;
            cout << "Got Response From Term: " << replyy.rcv_termnumber() << endl ;
            cout << "My Term: " << newNode.term << endl;
            cout << "Got Response: " << replyy.rcv_vote() << endl ;

            string re = replyy.rcv_vote()  + "Failed";
            return re;
        }
    }


    string sendNewStatusMsg(string& statusUpdate) 
    {

        // Data we are sending to the server.
        StringStatusUptateRequest request;

        request.set_status(statusUpdate);
        
        // Container for the data we expect from the server.
        StringStatusUptateReply replyy;

        // Context for the client. It could be used to convey extra information to
        // the server and/or tweak certain RPC behaviors.
        ClientContext context; 

        // The actual RPC.

        // ACTUAL SENDING MSG 
        Status status = stub_->sendStatusUpdateRequest(&context, request, &replyy);

        // Act upon its status.
        if (status.ok()) 
        {
            cout << "\nRECEIVED ACK: " << replyy.rcv_status() << endl ;

            return replyy.rcv_status(); 
        } 
        else 
        {
            string re = replyy.rcv_status()  + "Failed";
            return re;
        }
    }

    private:
    unique_ptr<MsgService::Stub> stub_;
  
};



int readFromConfigAndReturnCount()
{
    
    ifstream configFile("config.txt");
    if (!configFile) 
	{
        cout << "Could not open configuration File!\n";
        return 0;
    }

    int count = 0;
    string line;
    while (getline(configFile, line)) 
    {
        ++count;
    }
    return count;

}

vector<string> ReadFromConfig(string myaddress)
{
    // CONFIG FILE

	vector<string> nodes;

    ifstream configFile("config.txt");

    if (configFile.is_open()) 
    { 
        // Check if the input file was opened successfully
        string line;
        while (getline(configFile, line)) 
        { 
            // Read each line of the file
            if (line.find(myaddress) == string::npos) 
            { 
                // If myaddress is not found in the line, add the line to the vector
                nodes.push_back(line);
            }
        }
        configFile.close(); // Close the input file
    } 
    else 
    {
        cout << "Could not open config File!\n";
        return nodes;
    }
    return nodes;
}

// Function to extract the ID values from a vector of strings
vector<int> extractIds(const vector<string>& input) {
    vector<int> output; // Declare a vector of ints to store the ID values
    for (const auto& str : input) { // Iterate over each string in the input vector
        size_t pos = str.find(" "); // Find the first space character
        int id = stoi(str.substr(0, pos)); // Extract the ID value before the space and convert to int
        output.push_back(id); // Add the ID value to the output vector
    }
    return output; // Return the output vector
}

// Function to extract the addresses from a vector of strings
vector<string> extractAddresses(const vector<string>& input) {
    vector<string> output; // Declare a vector of strings to store the addresses
    for (const auto& str : input) { // Iterate over each string in the input vector
        size_t pos1 = str.find(" "); // Find the first space character
        size_t pos2 = str.find(" ", pos1 + 1); // Find the second space character
        string address = str.substr(pos1 + 1, pos2 - pos1 - 1); // Extract the address and port value
        output.push_back(address); // Add the address to the output vector
    }
    return output; // Return the output vector
}

// Function to extract the status values from a vector of strings
vector<string> extractStatuses(const vector<string>& input) {
    vector<string> output; // Declare a vector of strings to store the status values
    for (const auto& str : input) { // Iterate over each string in the input vector
        size_t pos = str.rfind(" "); // Find the last space character
        string status = str.substr(pos + 1); // Extract the status value after the space
        output.push_back(status); // Add the status value to the output vector
    }
    return output; // Return the output vector
}

void printVector(vector<string> input)
{
     for (size_t i = 0; i < input.size(); i++) 
     {
        cout << input[i] << endl;
    }
}
void printVectorInt(vector<int> input)
{
     for (size_t i = 0; i < input.size(); i++) 
     {
        cout << input[i] << endl;
    }
}

void checkAndWriteHeader(string filename, string header)
{
    ifstream file(filename);
    bool fileExists = file.good();
    
    if (!fileExists) 
    {
        ofstream newFile(filename);
        newFile << header << endl;
        newFile.close();
    } 
    else 
    {
        bool headerFound = false;
        string line;
        for (int i = 0; i < 2 && getline(file, line); i++) 
        {
            if (line == header) 
            {
                headerFound = true;
                break;
            }
        }
        file.close();
        
        if (!headerFound) 
        {
            ofstream outFile(filename, ios::app);
            outFile << header << endl;
            outFile.close();
        }
    }

}

// SENDS MESSAGES TO EACH NODE

void sendMessages(int nodeID, string nodeStatus, string address, string message)
{
    
    vector<string> ConfigList = ReadFromConfig(address);

    vector<int> ids = extractIds(ConfigList); // Extract the ID values
    vector<string> addresses = extractAddresses(ConfigList); // Extract the addresses
    vector<string> statuses = extractStatuses(ConfigList); // Extract the status values

    for(int i = 0; i < ConfigList.size(); i++)
    {
        this_thread::sleep_for (chrono::seconds(2));   
        
        newNode.term += 1;

        GreeterClient greeter(grpc::CreateChannel(addresses[i], grpc::InsecureChannelCredentials()));

        string reply = "";
        reply = reply + greeter.sendRequestt(nodeID, nodeStatus, message, addresses[i]);

        
        // // INTERFACE

        cout << "\n\t\tSENDING \n";                             
        cout << "\nSending Message to: " << addresses[i];                       
        cout << "\nMessage Sent: " << reply;                                    
        cout << "\nReceiver Id: " << ids[i];                                    
        cout << "\nReceiver Status: " << statuses[i] ;                          
        cout << "\nMy Term Number: " << newNode.term << "\n\n";                               

        // WRITING IN LOG FILE
        checkAndWriteHeader(newNode.filename, "Status\t\t\tId\t\tStatus\t\tterm\t\tmsg\t\tMyTerm");
        ofstream log_file(newNode.filename, ios::app);
        log_file << "SENT TO" << "\t" << "\t\t" << ids[i] << "\t\t" << statuses[i] << "\t" << "?" << "\t\t" << reply << "\t\t" << newNode.term << "\n";

    }
}



int count_lines(const string& filename) 
{
    ifstream file(filename);
    int count = 0;
    string line;
    while (getline(file, line)) 
    {
        ++count;
    }
    return count;
}

void wait_until_count_is_5(const string& filename) 
{
    int countt = 0;
    while (countt != 5)
    {
        // cout << "Count: " + countt;
        this_thread::sleep_for(chrono::seconds(2));
        countt = count_lines(filename);
    }
}

void deleteFile(const char* filename)
{
    if (filesystem::exists(filename)) 
    {
        int status = remove(filename);
        if (status == 0) {
            printf("File '%s' deleted successfully.\n", filename);
        } else {
            printf("Error deleting file '%s'.\n", filename);
        }
    } else {
        printf("File '%s' does not exist.\n", filename);
    }
}




// SENDING VOTING MESSAGES - CANDIDATE


int waitForRandomInterval()
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distr(1, 10); // Generate a random number between 1 and 10

    int wait_time = distr(gen); // Generate a random wait time
    cout << "\n\nWaiting for " << wait_time << " seconds before sending voting msgs\n\n" << endl;
    
    return wait_time;
}

void sendVoteMessages(int termNumber, string address)
{

    vector<string> ConfigList = ReadFromConfig(address);

    vector<int> ids = extractIds(ConfigList); // Extract the ID values
    vector<string> addresses = extractAddresses(ConfigList); // Extract the addresses
    vector<string> statuses = extractStatuses(ConfigList); // Extract the status values

    // WAITING FOR RANDOM INTERVAL
    int waitTime = waitForRandomInterval();
    this_thread::sleep_for(chrono::seconds(waitTime));


    vector <int> yesVotes;
    vector <int> noVotes;


    // SENDING VOTING MSGS
    for(int i = 0; i < ConfigList.size(); i++)
    {

        // INTERFACE

        cout << "\n\t\tSENDING VOTE REQUEST\n";

        cout << "\nSending Request to: " << addresses[i];

        //
        int returnVoterId;
        int returnVoterTerm;

        GreeterClient greeter(grpc::CreateChannel(addresses[i], grpc::InsecureChannelCredentials()));

        string reply = "";
        reply = reply + greeter.sendVoteRequestt(termNumber, newNode.filename, returnVoterId, returnVoterTerm);

        if (reply == "yes")
        {
            yesVotes.push_back(returnVoterId);

            if (yesVotes.size() >= ConfigList.size()/2 + 1)
            {
                newNode.status = "Leader";
                cout << endl  << "\tSTATUS CHANGED TO LEADER\n";

                
                string statusUpdateMsg = "NODE " + to_string(newNode.id) + " IS THE LEADER";
                // sends msgs to all other nodes 
                // SENDING 
                for(int i = 0; i < ConfigList.size(); i++)
                {
                    // INTERFACE

                    cout << "\n\t\tSENDING NEW STATUS MSG TO ALL NODES\n";

                    cout << "\nSending to: " << addresses[i];

                    GreeterClient greeter(grpc::CreateChannel(addresses[i], grpc::InsecureChannelCredentials()));

                    string reply = "";
                    reply = reply + greeter.sendNewStatusMsg(statusUpdateMsg);

                }

                return;
            }

        }
        else if (reply == "no")
        {

            if (termNumber < returnVoterTerm)
            {
                newNode.status = "Follower";
                cout << endl  << "STATUS CHANGED TO FOLLOWER\n";

            }
            else
            {
                cout << endl  << "ID OF NODE IS STORED IN VOTED NO LIST\n";
                noVotes.push_back(returnVoterId);
            }
        
        }

   
    }
}




int main(int argc, char *argv[]) 
{

	if (argc != 6) 
	{
        cout << "Provide Arguments as: " << argv[0] << " node_id node_status term_number node_address message\n";
        return 1;
    }

    if (string(argv[2]) != "Candidate" && string(argv[2]) != "Follower")
    {
        return 1;
    }   


    int id = stoi(argv[1]);

    string status = string(argv[2]);       // WRITE IN LOG FILE


    int term = stoi(argv[3]);
    string address = argv[4];
    string message = argv[5];
    

    string myLogFileName = "log" + to_string(id) + ".txt";


    newNode.id = id;
    newNode.status = status;
    newNode.term = term;
    newNode.address = address;
    newNode.filename = myLogFileName;

    cout << "Node " << newNode.id << " with status " << newNode.status << " and term number " 
         << newNode.term << " having address " << newNode.address << " started!\n";
    
	
    // WRITING IN CONFIG FILE

    ofstream outfile("config.txt", ios::app);
    outfile << newNode.id << " " << newNode.address << " " << newNode.status << endl;
    outfile.close();

    // READING FROM CONFIG
    string filename = "config.txt";
    wait_until_count_is_5(filename);




    // CALLING THREADS
    cout << "Thread Calls\n";

    // listening to message
    thread listenThread(listenForMessages, newNode.address);
    listenThread.detach();


    // Sending messages
    thread sendThread(sendMessages, newNode.id, newNode.status, newNode.address, message);
    sendThread.join();

    
    // listening to vote message
    thread listenVoteThread(listenForVoteMessages, newNode.address);
    
    

    // Sending Voting Call
    if (newNode.status == "Candidate")
    {   
        cout << "\nSENDING VOTE MSGS\n";

        
        thread sendVoteThread(sendVoteMessages, newNode.term, newNode.address);
        sendVoteThread.join();
    }
    
    listenVoteThread.join(); 
   

    return 0;


}