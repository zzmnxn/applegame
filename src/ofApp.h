#pragma once

#include "ofMain.h"
#include <vector>
#include <algorithm>
#include <random>
// 사용자 정보 구조체
struct User {
    std::string name;
    int score;
    User* next;

    User(std::string n, int s) : name(n), score(s), next(nullptr) {}
};

class ofApp : public ofBaseApp {
public:
    void setup(); // 초기 설정을 위한 함수
    void update(); // 매 프레임마다 업데이트를 위한 함수
    void draw(); // 화면에 그리기 위한 함수
    void keyPressed(int key);
    void mousePressed(int x, int y, int button); // 마우스 버튼을 눌렀을 때 호출되는 함수
    void mouseDragged(int x, int y, int button); // 마우스를 드래그할 때 호출되는 함수
    void mouseReleased(int x, int y, int button); // 마우스 버튼을 뗄 때 호출되는 함수
    ~ofApp(); //소멸자
private:
    void fillGrid(); // 그리드를 채우는 함수
    bool isValidPair(int x1, int y1, int x2, int y2); // 유효한 쌍인지 확인하는 함수
    bool isOverlapping(int x, int y, int w, int h, int x1, int y1, int x2, int y2); // 상자들이 겹치는지 확인하는 함수
    void drawModeSelection();
    void drawGame();
    void setupGame();
    void drawGameOver();
    void loadRanking();
    void saveRanking();
    void drawRanking();
    void addRanking(std::string name, int score);
    void displayRanking();
    void checkForExit(int key);
    
    void clearRankingList();// 랭킹 리스트의 메모리를 해제하는 함수
    const int gridSize = 10; // 그리드의 크기
    const int cellSize = 40; // 각 셀의 크기
    const int maxNumber = 9; // 셀에 들어가는 최대 숫자
    int grid[10][10]; // 숫자를 저장하는 그리드
    int score; // 점수
    float timer; // 남은 시간
    const float timeLimit = 10.0f; // 제한 시간
    int mode;//게임 모드
    bool gameOver; // 게임 오버 상태
    bool drawingBox; // 상자가 그려지고 있는지 여부
    ofPoint startPoint, endPoint; // 상자의 시작점과 끝점
    User* rankingList; // 랭킹 리스트
    std::string playerName; // 현재 플레이어 이름 입력
    bool enteringName; // 이름 입력 상태
    std::vector<std::pair<int, int>> getValidPairs(); // 유효한 숫자 쌍을 반환하는 함수
    bool shouldExit = false;
};
