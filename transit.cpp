#include<iostream>
#include<string>
using namespace std;

const int value = 100;
const int NUM_STATIONS = 11;

struct Station;

struct Edge {
    int timeTravel;
    Station *to;
    Edge *eNext;
};

struct Station {
    string name;
    Edge *eC;
};

// global station list
Station sList[NUM_STATIONS] = {
    {"Muzium Negara", NULL}, {"Pasar Seni", NULL}, {"KL Sentral", NULL}, {"Masjid Jamek", NULL},
    {"Bandaraya", NULL}, {"Merdeka", NULL}, {"Hang Tuah", NULL}, {"Bukit Bintang", NULL}, 
    {"Tun Razak Exchange", NULL}, {"Dang Wangi", NULL}, {"Kampung Baru", NULL}
};

void addEdge(int timeTravel, Station* from, Station *to) {
    Edge* newEdge = new Edge;
    newEdge->timeTravel = timeTravel;
    newEdge->to = to;
    newEdge->eNext = from->eC;
    from->eC = newEdge;
}

void buildGraph() {
    addEdge(2,&sList[0],&sList[1]); // MN -> PS
    
    addEdge(3,&sList[1],&sList[2]); // PS -> KLS
    addEdge(2,&sList[1],&sList[3]); // PS -> MJ
    addEdge(1,&sList[1],&sList[5]); // PS -> M
    addEdge(2,&sList[1],&sList[0]); // PS -> MN
    
    addEdge(3,&sList[2],&sList[1]); // KLS -> PS
    
    addEdge(2,&sList[3],&sList[4]); // MJ -> B
    addEdge(2,&sList[3],&sList[1]); // MJ -> PS
    addEdge(1,&sList[3],&sList[5]); // MJ -> M
    addEdge(1,&sList[3],&sList[9]); // MJ -> DW
    
    addEdge(2,&sList[4],&sList[3]); // B -> MJ
    
    addEdge(1,&sList[5],&sList[6]); // M -> HT
    addEdge(1,&sList[5],&sList[1]); // M -> PS
    addEdge(1,&sList[5],&sList[3]); // M -> MJ
    addEdge(2,&sList[5],&sList[2]); // M -> BB
    
    addEdge(1,&sList[6],&sList[5]); // HT -> M
    
    addEdge(2,&sList[7],&sList[5]); // BB -> M
    addEdge(3,&sList[7],&sList[8]); // BB -> TRX
    
    addEdge(3,&sList[8],&sList[7]); // TRX -> BB
    
    addEdge(1,&sList[9],&sList[3]); // DW -> MJ
    addEdge(2,&sList[9],&sList[10]);// DW -> KB
    
    addEdge(2,&sList[10],&sList[9]);// KB -> DW
}

void findShortestPath(int startIdx, int endIdx) {
    int dist[NUM_STATIONS];
    bool visited[NUM_STATIONS] = {false};
    int prev[NUM_STATIONS];

    for (int i = 0; i < NUM_STATIONS; i++) {
        dist[i] = value;// initiate all stations is far away
        prev[i] = -1;// no previous station 
    }
    dist[startIdx] = 0;// from source station to source station is 0

    //to find the shrtest path
    for (int i = 0; i < NUM_STATIONS; i++) {
        int u = -1; //to select station that havent visited
        for (int j = 0; j < NUM_STATIONS; j++) { // loop in the stations which havent visited yet
            if (!visited[j] && (u == -1 || dist[j] < dist[u]))// if this station hasnt visited any station and the time is less than before
                u = j; // update the new path
        }
        
        // to update the status of station
        if (dist[u] == value) break;
        visited[u] = true;
        
        //check neighbour
        for (Edge* e = sList[u].eC; e != nullptr; e = e->eNext) {
            int v = -1; // run all neighbour
            for (int i = 0; i < NUM_STATIONS; i++) {
                if (&sList[i] == e->to) {// find this neighbour is refer to which station
                    v = i; //update the index 
                    break;
                }
            }
            if (v != -1 && dist[u] + e->timeTravel < dist[v]) { // if v is valid and the path is shorter than before
                dist[v] = dist[u] + e->timeTravel;// update new path
                prev[v] = u; // record in previous pathway list
            }
        }
    }

    // print the total time and path
    cout << "\nShortest travel time: " << dist[endIdx] << " minutes" << endl;
    cout << "Path: ";
    int path[NUM_STATIONS], count = 0;
    //reconstruct path
    for (int at = endIdx; at != -1; at = prev[at]) {
        path[count++] = at;
    }
    //display the path
    for (int i = count - 1; i >= 0; i--) {
        cout << sList[path[i]].name;
        if (i != 0) cout << " -> ";
    }
    cout << endl;
}

int main() {
    buildGraph();
    int startIdx, endIdx;
    int fromNum, toNum;

    cout << "\n== Station List ==" << endl;
    for (int i = 0; i < NUM_STATIONS; ++i)
        cout << (i + 1) << ". " << sList[i].name << endl;

    cout << "\nEnter 0 at any point to exit.\n" << endl;

    // Get source
    do {
        cout << "Enter source station number (1-" << NUM_STATIONS << "): ";
        cin >> fromNum;
        if (fromNum == 0) {
            cout << "Exiting..." << endl;
            return 0;
        }
        startIdx = fromNum - 1;
        if (startIdx < 0 || startIdx >= NUM_STATIONS)
            cout << "Invalid source station. Try again.\n";
    } while (startIdx < 0 || startIdx >= NUM_STATIONS);

    // Get destination
    do {
        cout << "Enter destination station number (1-" << NUM_STATIONS << "): ";
        cin >> toNum;
        if (toNum == 0) {
            cout << "Exiting..." << endl;
            return 0;
        }
        endIdx = toNum - 1;
        if (endIdx < 0 || endIdx >= NUM_STATIONS)
            cout << "Invalid destination station. Try again.\n";
    } while (endIdx < 0 || endIdx >= NUM_STATIONS);

    findShortestPath(startIdx, endIdx);
    return 0;
}
