#include "Player.hh"


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME ElonMusk_v2


struct PLAYER_NAME : public Player {

  /**
   * Factory: returns a new instance of this class.
   * Do not modify this function.
   */
  static Player* factory () {
    return new PLAYER_NAME;
  }

  //VARIABLES
  const vector<Dir> dirs = {RIGHT, TOP, BOTTOM, LEFT};

  int idPlayer, numUnits;
  vector<int> myUnits;

  enum unitAct { //Unit actions
    conquere,
    agressive,
    noneU
  };

  map<int, unitAct> UA; //map of character actions, idU as key
  
  //OPERATORS
  bool coolPos(const Pos p) {
    bool myCell = false;
    for (int i = 0; i < numUnits; ++i) {
      if (myUnits[i] == cell(p).unit_id) myCell = true; 
    }
    return not myCell and pos_ok(p) and cell(p).type != WALL;
  }

  bool bonusPos(const Pos p){
    /*bool conqC = false; 
    bool conqP = false;
    if (cell(p).type == CITY){
      if (city_owner(cell(p).city_id) == idPlayer) conqC = true;
    }
    if (cell(p).type == PATH){
      if (path_owner(cell(p).city_id) == idPlayer) conqP = true;
    }
    bool cond = not conqC and not conqP;*/
    return (cell(p).type == CITY or cell(p).type == PATH);
  }
  
  bool enemy(const int id){
    if (id == -1) return false;
    for(int i = 0; i < numUnits; ++i){
      if (myUnits[i] == id) return false;
    }
    return true;
  }

  bool Conq(const Cell cell){
    if (cell.type == CITY){
      if (city_owner(cell.city_id) == idPlayer) return true;
    }
    if (cell.type == PATH){
      if (path_owner(cell.city_id) == idPlayer) return true;
    }
    return false;
  }

  void initializeData(){
    idPlayer = me();
  }

  void initializeRound(){
    myUnits = my_units(idPlayer);
    numUnits = myUnits.size();
    UA.clear();
    for(auto p : myUnits) UA.insert(make_pair(p, agressive));
  }

  //ALGORITHMS
  Dir randomMove(const Pos initPos, bool& found){
    found = true;
    vector<Dir> q;
    for(auto d : dirs) if(coolPos(initPos + d)) q.push_back(d);
    int r = rand() % q.size();
    if(q.size() > 0) return q[r];
    else {
      found = false;
      return TOP;
    }
  }

  Dir cellDirection(const Pos initPos, const CellType typeCell, bool& found) {
    found = true;
   	vector<vector<bool> > binariBoard(cols(), vector<bool>(rows(), false));
   	binariBoard[initPos.i][initPos.j] = true;
   	queue<pair<Dir, Pos> > q;

   	// posible initial moves and base case
   	for(auto d : dirs) {
   		Pos p = initPos + d;
   		if(coolPos(p)) { 
     		if(cell(p).type == typeCell and not Conq(cell(p))) return d;
     		else {
     			q.push(make_pair(d,p));
     			binariBoard[p.i][p.j] = true;
     		}
   		} 
    }
    // only one posible move
    if(q.size() == 1) return q.front().first;
   	// bfs algorithm
   	pair<Dir,Pos> act;
   	while(not q.empty()) {
   		act = q.front();
   		q.pop();
   		for(auto d : dirs) { // where we can go?
   			Pos nextMove = act.second + d;
   			if(coolPos(nextMove) and binariBoard[nextMove.i][nextMove.j] == false) { // cool move
          binariBoard[nextMove.i][nextMove.j] = true;
          q.push(make_pair(act.first, nextMove));    // we visit it
   				if(cell(nextMove).type == typeCell and not Conq(cell(nextMove))) {      // is where i want to go?
   					return act.first;
          }                   
   			}
   		}
   	}
   	// default return not found cell
  	found = false;
  	return TOP;
  }

  Dir pathDirection(const Pos initPos, const CellType typeCell, bool& found) {
    found = true;
   	vector<vector<bool> > binariBoard(cols(), vector<bool>(rows(), false));
   	binariBoard[initPos.i][initPos.j] = true;
   	queue<pair<Dir, Pos> > q;

   	// posible initial moves and base case
   	for(auto d : dirs) {
   		Pos p = initPos + d;
   		if(coolPos(p) and bonusPos(p)) { 
     		if(cell(p).type == typeCell and not Conq(cell(p))) return d;
     		else {
     			q.push(make_pair(d,p));
     			binariBoard[p.i][p.j] = true;
     		}
   		} 
    }
    // only one posible move
    if(q.size() == 1) return q.front().first;
   	// bfs algorithm
   	pair<Dir,Pos> act;
   	while(not q.empty()) {
   		act = q.front();
   		q.pop();
   		for(auto d : dirs) { // where we can go?
   			Pos nextMove = act.second + d;
   			if(coolPos(nextMove) and binariBoard[nextMove.i][nextMove.j] == false and bonusPos(nextMove)) { // cool move
          binariBoard[nextMove.i][nextMove.j] = true;
          q.push(make_pair(act.first, nextMove));    // we visit it
   				if(cell(nextMove).type == typeCell and not Conq(cell(nextMove))) {      // is where i want to go?
   					return act.first;
          }                   
   			}
   		}
   	}
   	// default return not found cell
  	found = false;
  	return TOP;
  }

  Dir maskDirection(const Pos initPos, bool& found) {
    found = true;
   	vector<vector<bool> > binariBoard(cols(), vector<bool>(rows(), false));
   	binariBoard[initPos.i][initPos.j] = true;
   	queue<pair<Dir, Pos> > q;

   	// posible initial moves and base case
   	for(auto d : dirs) {
   		Pos p = initPos + d;
   		if(coolPos(p)) { 
     		if(cell(p).mask) return d;
     		else {
     			q.push(make_pair(d,p));
     			binariBoard[p.i][p.j] = true;
     		}
   		} 
    }
    // only one posible move
    if(q.size() == 1) return q.front().first;
   	// bfs algorithm
   	pair<Dir,Pos> act;
   	while(not q.empty()) {
   		act = q.front();
   		q.pop();
   		for(auto d : dirs) { // where we can go?
   			Pos nextMove = act.second + d;
   			if(coolPos(nextMove) and binariBoard[nextMove.i][nextMove.j] == false) { // cool move
          binariBoard[nextMove.i][nextMove.j] = true;
          q.push(make_pair(act.first, nextMove));    // we visit it
   				if(cell(nextMove).mask) {      // is where i want to go?
   					return act.first;
          }                   
   			}
   		}
   	}
   	// default return not found cell
  	found = false;
  	return TOP;
  }

  Dir enemyDirection(const Pos initPos, bool& found) {
    found = true;
   	vector<vector<bool> > binariBoard(cols(), vector<bool>(rows(), false));
   	binariBoard[initPos.i][initPos.j] = true;
   	queue<pair<Dir, Pos> > q;

   	// posible initial moves and base case
   	for(auto d : dirs) {
   		Pos p = initPos + d;
   		if(coolPos(p)) { 
     		if(enemy(cell(p).unit_id)) return d;
     		else {
     			q.push(make_pair(d,p));
     			binariBoard[p.i][p.j] = true;
     		}
   		} 
    }
    // only one posible move
    if(q.size() == 1) return q.front().first;
   	// bfs algorithm
   	pair<Dir,Pos> act;
   	while(not q.empty()) {
   		act = q.front();
   		q.pop();
   		for(auto d : dirs) { // where we can go?
   			Pos nextMove = act.second + d;
   			if(coolPos(nextMove) and binariBoard[nextMove.i][nextMove.j] == false) { // cool move
          binariBoard[nextMove.i][nextMove.j] = true;
          q.push(make_pair(act.first, nextMove));    // we visit it
   				if(enemy(cell(nextMove).unit_id)) {      // is where i want to go?
   					return act.first;
          }                   
   			}
   		}
   	}
   	// default return not found cell
  	found = false;
  	return TOP;
  }

  //IA OF MY UNITS
  void unitIA(const int id) {
    Unit u = unit(id);
    const int life =  u.health;
    bool found = true;
    bool enemy;
    Dir nextMove;

    switch(UA[id]){
      case conquere:
        //UNIT on city
        if (cell(u.pos).type == CITY) {
          //attack if enemy
          enemy = true;
          for (auto d : dirs){
            Pos p = u.pos + d;
            if (cell(p).unit_id == -1) enemy = false;//there is a unit
            else{
              for(int i = 0; i < numUnits; ++i){
                if (myUnits[i] == cell(p).unit_id) enemy = false;
              }
            }
            if (enemy) {
              if (unit(cell(p).unit_id).health > u.health) {
                nextMove = pathDirection(u.pos, PATH, found);
                move(id, nextMove);
                break;
              }
              else {
                move(id, d);
                break;
              }
            }
          }
          //avoid virus
          Dir dirLess = NONE;
          int virus = cell(u.pos).virus;
          for (auto d : dirs){
            Pos p = u.pos + d;
            if (cell(p).type == CITY or cell(p).type == PATH){
              if (cell(p).virus < virus) dirLess = d;
            }
          }
          if (dirLess != NONE) {
            move(id, dirLess);
            break;
          }
          //if city conquered, move to path
          if (city_owner(cell(u.pos).city_id) == idPlayer) {
            nextMove = pathDirection(u.pos, PATH, found);
            if (found) {
              move(id, nextMove);
              break;
            }
          }
        }
        //UNIT on path
        else if (cell(u.pos).type == PATH) {
          //attack if enemy
          bool enemy = true;
          for (auto d : dirs){
            Pos p = u.pos + d;
            if (cell(p).unit_id == -1) enemy = false;//there is a unit
            else{
              for(int i = 0; i < numUnits; ++i){
                if (myUnits[i] == cell(p).unit_id) enemy = false;
              }
            }
            if (enemy) {
              move(id, d);
              break;
            }
          }
          //avoid virus
          Dir dirLess = NONE;
          int virus = cell(u.pos).virus;
          for (auto d : dirs){
            Pos p = u.pos + d;
            if (cell(p).type == CITY or cell(p).type == PATH){
              if (cell(p).virus < virus) dirLess = d;
            }
          }
          if (dirLess != NONE) {
            move(id, dirLess);
            break;
          }
          //if path conquered, move to city
          if (path_owner(cell(u.pos).path_id) == idPlayer) {
            cerr << "PATH conquered __________________" << endl;
            nextMove = pathDirection(u.pos, CITY, found);
            if (found) {
              move(id, nextMove);
              break;
            }
          }
        }
        else { //conquere city/path
          nextMove = cellDirection(u.pos, CITY, found);
          //cerr << "SEARCHING CITY" << endl;
          if (found) {
            move(id, nextMove);
            break;
          }
          else {
            nextMove = cellDirection(u.pos, PATH, found);
            cerr << "SEARCHING PATH" << endl;
            if (found) {
            move(id, nextMove);
            break;
            }
            else {
              cerr << "RANDOM MOVE" << endl;
              nextMove = randomMove(u.pos, found);
              if (found) move(id, nextMove);
              else move(id, NONE);
            }
          }
        }
        break;

      case agressive:
        //atack if enemy
        for (auto d : dirs){
          enemy = true;
          Pos p = u.pos + d;
          if (cell(p).unit_id == -1) enemy = false;//there is a unit?
          else{
            for(int i = 0; i < numUnits; ++i){
              if (myUnits[i] == cell(p).unit_id) enemy = false;
            }
          }
          if (enemy) {
            if (unit(cell(p).unit_id).health > u.health){//run
              nextMove = cellDirection(u.pos, CITY, found);
              move(id, nextMove);
              break;
            }
            else {//attack
              move(id, d);
              break;
            }
          }
        }
        if (not enemy) {//NO near enemy
          if (u.damage > 0 and not u.mask) {//unit infected and not has a mask
            nextMove = maskDirection(u.pos, found);
            if (found) {
              move(id, nextMove);
              break;
            }
            else{//mask not found
              nextMove = enemyDirection(u.pos, found);
              if (found){
                move(id, nextMove);
                break;
              }
            }
          }
          else {//unit not infected
            //avoid virus if not inmune
            Dir dirLess = NONE;
            int virus = cell(u.pos).virus;
            for (auto d : dirs){
              Pos p = u.pos + d;
              if (cell(p).virus < virus) dirLess = d;
            }
            if (dirLess != NONE and (not u.immune)) {
              move(id, dirLess);
              break;
            }
            else{//same amount of virus everywhere
              if (cell(u.pos).type == CITY){
                //if city conquered, move to path
                if (city_owner(cell(u.pos).city_id) == idPlayer) {
                  nextMove = pathDirection(u.pos, PATH, found);
                  if (found) {
                    move(id, nextMove);
                    break;
                  }
                }
              }
              else if (cell(u.pos).type == PATH){
                if (path_owner(cell(u.pos).path_id) == idPlayer) {
                  nextMove = pathDirection(u.pos, CITY, found);
                  if (found) {
                    move(id, nextMove);
                    break;
                  }
                }
              }
              else { //we'r in grass
                nextMove = cellDirection(u.pos, CITY, found);
          //cerr << "SEARCHING CITY" << endl;
                if (found) {
                  move(id, nextMove);
                  break;
                }
                else {
                  nextMove = cellDirection(u.pos, PATH, found);
                  if (found) {
                    move(id, nextMove);
                    break;
                  }
                }
              }
            }
          }
        }
        break;
      case noneU:
        //case none action move
        break;
    }
  }
  

  virtual void play () {
    //INIT
    if(status(idPlayer) > 0.9) return;
    if(round() == 0) initializeData();

    //ROUND
    initializeRound();
    for(auto u : myUnits) unitIA(u);

  }

};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);