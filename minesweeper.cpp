#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <vector>
using namespace std;

struct Block{
    int coorx,coory,loc,bombaround;
    bool visible = false;
    bool bomb;
    Block(int x,int y,int num, bool danger = false):coorx(x),coory(y), loc(num), bomb(danger){}
};

class Minesweeper{
    int bombnumber;
    vector<vector<Block>> graph;
    vector<int> surroundings(int loc){
        vector<int> answer{loc-13,loc-12,loc-11,loc-1,loc+1,loc+11,loc+12,loc+13};
        return answer;
    }
    Block& loc_to_block(int loc){
        int x = loc % 12;
        int y = loc / 12;
        return graph[y][x];
    }
public:
    Minesweeper(int num = 10):bombnumber(num){
        // initialize a vector of all bombs
        srand (time(NULL));
        int count = 0;
        for (int i = 0; i < 12; ++i){
            vector<Block> line;
            for (int j = 0; j< 12; ++j){
                if (count <= 12 || count % 12 == 0 || count%12 == 11 || count>131){
                    line.push_back(Block(j,i,count,false));
                }
                else if (rand()%100 < num) {
                    line.push_back(Block(j, i,count, true));
                }else{line.push_back(Block(j,i,count,false));}
                count ++;
            }
            graph.push_back(line);
        }
        // determine bombaround for each of them
        for (int i = 1; i < 11; ++i){
            for (int j = 1; j < 11; ++j){
                int loc= graph[j][i].loc;
                Block& block = graph[j][i];
                vector<int> surrounding = surroundings(loc);
                count = 0;
                for (int num:surrounding){
                    if (loc_to_block(num).bomb){
                        count++;
                    }
                }
                block.bombaround = count;
            }
        }
    }
    void display(bool answer)const{
        if(answer){
            for(int i = 1; i<11;i++){
                for(int j = 1; j<11;++j){
                    const Block& block = graph[j][i];
                    if (block.bomb){
                        cout << "*|";
                    }else{
                        cout << "_|";
                    }
                }
                cout << endl;
            }
        }else{
            for(int i = 1;i<11;i++){
                for(int j = 1;j<11;j++){
                    const Block& block = graph[j][i];
                    if (block.visible){
                        cout << block.bombaround << "|";
                    } else{
                        cout << "_|";
                    }
                }
                cout << endl;
            }
        }
    }; //if true: allbombs, else:blank
    bool done()const{
        for (int i = 1; i< 11; ++i){
            for (int j = 1; j< 11; ++j){
                const Block& block = graph[j][i];
                if(!(block.bomb)){
                    if(!(block.visible)){
                        return false;
                    }
                }
            }
        }
        return true;
    }; // Returns true if the game is over, false otherwise
    bool validRow(int row)const{
        return (row >= 1 && row <= 10);
    }
    bool validCol(int col)const{
        return (col >=1 && col <= 10);
    }
    bool isVisible(int row, int col)const{
        const Block& block = graph[col][row];
        return block.visible;
    };
    bool play(int row, int col){
        vector<int> todo;
        Block& block = graph[col][row];
        todo.push_back(block.loc);
        while (!todo.empty()) {
            Block& ablock = loc_to_block(todo.back());
            todo.pop_back();
            if (ablock.loc <= 12 || ablock.loc % 12 == 0 || ablock.loc%12 == 11 || ablock.loc>131){
                continue;
            }
            if (ablock.visible){
                continue;
            }
            if (ablock.bomb) {
                return false;
            }
            ablock.visible = true;
            if (ablock.bombaround == 0) {
                vector<int> surround = surroundings(ablock.loc);
                for(int k:surround){
                    todo.push_back(k);
                }
            }
        }
        return true;
    };
};


int main() {
    Minesweeper sweeper;
    // Continue until only invisible cells are bombs
    while (!sweeper.done()) {
        sweeper.display(false); // display board without bombs
        int row_sel = -1, col_sel = -1;
        while (row_sel == -1) {
            // Get a valid move
            int r, c;
            cout << "row? ";
            cin >> r;
            if (!sweeper.validRow(r)) {
                cout << "Row out of bounds\n";
                continue;
            }
            cout << "col? ";
            cin >> c;
            if (!sweeper.validCol(c)) {
                cout << "Column out of bounds\n";
                continue;
            }
            if (sweeper.isVisible(r,c)) {
                cout << "Square already visible\n";
                continue;
            }
            row_sel = r;
            col_sel = c;
        }
        // Set selected square to be visible. May effect other cells.
        if (!sweeper.play(row_sel,col_sel)) {
            cout << "Sorry, you died..\n";
            sweeper.display(true); // Final board with bombs shown
            exit(0);
        }
    }
    // Ah! All invisible cells are bombs, so you won!
    cout << "You won!!!!\n";
    sweeper.display(true); // Final board with bombs shown
}