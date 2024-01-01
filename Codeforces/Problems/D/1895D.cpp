#include <bits/stdc++.h>

using namespace std;
struct trie
{
    int value;
    trie *child[2];
};

// Function to initialise a Trie Node
trie * get()
{
    trie * root = new trie;
    root -> value = 0;
    root -> child[0] = NULL;
    root -> child[1] = NULL;
    return root;
}

// Computing max xor
int max_xor(trie * root, int key)
{
    trie * temp = root;

    // Checking for all bits in integer range
    for (int i = 31; i >= 0; i--)
    {
        // Current bit in the number
        bool current_bit = ( key & ( 1 << i) );

        // Traversing Trie for different bit, if found
        if (temp -> child[1 - current_bit] != NULL)
            temp = temp -> child[1 - current_bit];

            // Traversing Trie for same bit
        else
            temp = temp -> child[current_bit];
    }

    // Returning xor value of maximum bit difference
    // value. Thus, we get maximum xor value
    return (key ^ temp -> value);
}

// Inserting B[] in Trie
void insert(trie * root, int key)
{
    trie * temp = root;

    // Storing 31 bits as integer representation
    for (int i = 31; i >= 0; i--)
    {
        // Current bit in the number
        bool current_bit = key & (1 << i);

        // New node required
        if (temp -> child[current_bit] == NULL)
            temp -> child[current_bit] = get();

        // Traversing in Trie
        temp = temp -> child[current_bit];
    }
    // Assigning value to the leaf Node
    temp -> value = key;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;
    int a[n-1], p[n-1];
    for (int i = 0; i < n-1; i++){
        cin >> a[i];
        p[i] = (i == 0 ? a[0] : p[i-1] ^ a[i]);
    }
    trie * root = get();
    for (int i = 0; i < n-1; i++){
        insert(root, p[i]);
    }

    auto test = [&](int b0) -> bool{
        set<int> seen; seen.insert(b0);
        for (int i = 0; i < n-1; i++){
            if (seen.contains(b0 ^ p[i])) return false;
            seen.insert(b0 ^ p[i]);
        }
        return true;
    };

    for (int i = 0; i < n; i++){
        if (max_xor(root, i) < n){
            //set b[0] to be i
            if (test(i)){
                cout << i << " ";
                for (int j = 0; j < n-1; j++){
                    cout << (i ^ p[j]) << " ";
                }
                cout << "\n";
                break;
            }
        }
    }
}