

#ifndef _MAINBOARD_H_
#define _MAINBOARD_H_

class MainBoard {
  private:
    int id;

  public:
    MainBoard();
    /// get board ID from dip switch
    int getId();


};


#endif
