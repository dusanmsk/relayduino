#ifndef BOARD_H_
#define BOARD_H_



class Board {
private:
  int configButtonPin;
  int ledPin;
  int boardId;
  String boardIdStr;
  void runInitialConfigFlow();
  void awaitBoardConfiguration();
public:
  Board(int ledPin, int configButtonPin);
  void initialize();
  bool isConfigButtonPressed();
  void blinkLed(int timeMs);
  void setLed(int value);
  void blinkBoardId();
  const String getBoardIdStr() { return boardIdStr; }
  const int getBoardId() { return boardId; }

};


#endif
