// Datastructures.hh

#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include <string>
#include <vector>
#include <utility>
#include <limits>
#include <stack>



// Type for beacon IDs
using BeaconID = std::string;
using BeaconName = std::string;

// Return value for cases where required beacon was not found
BeaconID const NO_ID = "----------";

// Return value for cases where integer values were not found
int const NO_VALUE = std::numeric_limits<int>::min();

// Return value for cases where name values were not found
std::string const NO_NAME = "-- unknown --";

// Type for a coordinate (x, y)
struct Coord
{
    int x = NO_VALUE;
    int y = NO_VALUE;
};

// Example: Defining == and hash function for Coord so that it can be used
// as key for std::unordered_map/set, if needed
inline bool operator==(Coord c1, Coord c2) { return c1.x == c2.x && c1.y == c2.y; }
inline bool operator!=(Coord c1, Coord c2) { return !(c1==c2); } // Not strictly necessary

struct CoordHash
{
    std::size_t operator()(Coord xy) const
    {
        auto hasher = std::hash<int>();
        auto xhash = hasher(xy.x);
        auto yhash = hasher(xy.y);
        // Combine hash values (magic!)
        return xhash ^ (yhash + 0x9e3779b9 + (xhash << 6) + (xhash >> 2));
    }
};


// Example: Defining < for Coord so that it can be used
// as key for std::map/set
inline bool operator<(Coord c1, Coord c2)
{
    if (c1.y < c2.y) { return true; }
    else if (c2.y < c1.y) { return false; }
    else { return c1.x < c2.x; }
}

// Return value for cases where coordinates were not found
Coord const NO_COORD = {NO_VALUE, NO_VALUE};

// Type for color (RGB)
struct Color
{
    int r = NO_VALUE;
    int g = NO_VALUE;
    int b = NO_VALUE;
};

struct BeaconData
{
    std::string name;
    BeaconID id;
    std::vector<BeaconID> master;
    Coord xy;
    Color color;
    double brightness_;
    int initial_distance;
    int *dist;
    BeaconID vassal;
};

struct Node{
    BeaconID id;
    struct Node *nxt;
};
// Equality and non-equality comparisons for Colors
inline bool operator==(Color c1, Color c2) { return c1.r == c2.r && c1.g == c2.g && c1.b == c2.b; }
inline bool operator!=(Color c1, Color c2) { return !(c1==c2); }

// Return value for cases where color was not found
Color const NO_COLOR = {NO_VALUE, NO_VALUE, NO_VALUE};

// Type for light transmission cost (used only in the second assignment)
using Cost = int;

// Return value for cases where cost is unknown
Cost const NO_COST = NO_VALUE;


// This is the class you are supposed to implement

class Datastructures
{
public:
    Datastructures();
    ~Datastructures();

    // Estimate of performance:Theta(1)
    // Short rationale for estimate: It is a constant computation.
    int beacon_count();

    // Estimate of performance:Theta(1)
    // Short rationale for estimate: It is a constant computation.
    void clear_beacons();

    // Estimate of performance: Theta(n)
    // Short rationale for estimate: This is a linea computation.
    std::vector<BeaconID> all_beacons();

    // Estimate of performance: O(1)
    // Short rationale for estimate:The elements in the unordered_map are not sorted in
    // any particular order with respect to either their key or mapped values, but organized
    // into buckets depending on their hash values to allow for fast access to individual
    bool add_beacon(BeaconID id, std::string const& name, Coord xy, Color color);

    // Estimate of performance: O(1)
    // Short rationale for estimate:Unordered map is an associative container that contains key-value pairs with unique keys.
    // Search of elements have average constant-time complexity.
    std::string get_name(BeaconID id);

    // Estimate of performance: O(1)
    // Short rationale for estimate:Unordered map is an associative container that contains key-value pairs with unique keys.
    // Search of elements have average constant-time complexity.
    Coord get_coordinates(BeaconID id);

    // Estimate of performance:O(1)
    // Short rationale for estimate:Unordered map is an associative container that contains key-value pairs with unique keys.
    // Search of elements have average constant-time complexity.
    Color get_color(BeaconID id);

    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance:O(n)
    // Short rationale for estimate:is an associative container that contains key-value pairs with unique keys.
    // Search of elements have average constant-time complexity. For the sorting part,the complexity is linear computation.
    std::vector<BeaconID> beacons_alphabetically();

    // Estimate of performance:O(n)
    // Short rationale for estimate: Unordered map is an associative container that contains key-value pairs with unique keys.
    // Search, insertion and removal of elements have average constant-time complexity. Incrementing an iterator is constant time,  so iterating through
    // all the elements of the container is O(N). So, the complexity of the average case is Big-O(n).
    std::vector<BeaconID> beacons_brightness_increasing();

    // Estimate of performance:O(n)
    // Short rationale for estimate:Unordered map is an associative container that contains key-value pairs with unique keys.
    // Search and insertion of elements have average constant-time complexity. Incrementing an iterator is constant time,  so iterating through
    BeaconID min_brightness();

    // Estimate of performance:O(n)
    // Short rationale for estimate:Unordered map is an associative container that contains key-value pairs with unique keys.
    // Search and insertion of elements have average constant-time complexity. Incrementing an iterator is constant time,  so iterating through
    BeaconID max_brightness();

    // Estimate of performance:O(n)
    // Short rationale for estimate:Unordered map is an associative container that contains key-value pairs with unique keys.
    // Search of elements have average constant-time complexity. Incrementing an iterator is constant time,  so iterating through
    // all the elements of the container is O(N).
    std::vector<BeaconID> find_beacons(std::string const& name);

    // Estimate of performance:O(1)
    // Short rationale for estimate: Unordered map is an associative container that contains key-value pairs with unique keys.
    // Search of elements have average constant-time complexity.
    bool change_beacon_name(BeaconID id, std::string const& newname);

    // Estimate of performance:O(1)
    // Short rationale for estimate:Unordered map is an associative container that contains key-value pairs with unique keys.
    // Search of elements have average constant-time complexity.
    bool change_beacon_color(BeaconID id, Color newcolor);

    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance O(nm)
    // Short rationale for estimate: In our case, we use the adjacency list structure for graphs.
    // n means the number of all nodes and m means the number of all children in each node.
    bool add_lightbeam(BeaconID sourceid, BeaconID targetid);

    // Estimate of performance: The average case is Big-O(n).
    // Short rationale for estimate: Unordered map is an associative container that contains key-value pairs with unique keys.
    // Search and insertion of elements have average constant-time complexity. Incrementing an iterator is constant time,  so iterating through
    // all the elements of the container is O(N). So, the complexity of the average case is Big-O(n).
    std::vector<BeaconID> get_lightsources(BeaconID id);

    // Estimate of performance:O(nm)
    // Short rationale for estimate: In our case, we use the adjacency list structure for graphs.
    // n means the number of all nodes and m means the number of all children in each node.
    std::vector<BeaconID> path_outbeam(BeaconID id);

    // Non-compulsory operations

    // Estimate of performance:O(m)
    // Short rationale for estimate: In our case, we use the adjacency list structure for graphs.
    // n means the number of all nodes and m means the number of all children in each node.
    bool remove_beacon(BeaconID id);

    // Estimate of performance:The average case is Big-O(nlogn)
    // Short rationale for estimate:Use recussive method to get the vassals. The complexity of the average case is Big-O(logn).
    // Unordered map is an associative container that contains key-value pairs with unique keys.
    // Search of elements have average constant-time complexity.
    std::vector<BeaconID> path_inbeam_longest(BeaconID id);

    // Estimate of performance: O((n+m)logn)
    // Short rationale for estimate: In this case, we use Dijkstra's algorithm.
    Color total_color(BeaconID id);

private:
    void quick_sort_name(std::vector<BeaconData*>& beaconlist, int left, int right);
    void quick_sort_brightness(std::vector<BeaconData*>& beaconlist, int left, int right);
    // Add stuff needed for your class implementation here
    std::vector<BeaconData*> beaconlist_;
//   std::vector <BeaconName> namelist_;
    std::vector<BeaconID> brightness_increasing;
    std::pair<BeaconID, BeaconData*> beaconlist_p;
    std::vector<BeaconID> IDlist_;

};

#endif // DATASTRUCTURES_HH
