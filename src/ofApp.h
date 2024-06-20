#pragma once

#include "ofMain.h"
#include <vector>
#include <algorithm>
#include <random>

class ofApp : public ofBaseApp {
public:
    void setup(); // �ʱ� ������ ���� �Լ�
    void update(); // �� �����Ӹ��� ������Ʈ�� ���� �Լ�
    void draw(); // ȭ�鿡 �׸��� ���� �Լ�
    void keyPressed(int key);
    void mousePressed(int x, int y, int button); // ���콺 ��ư�� ������ �� ȣ��Ǵ� �Լ�
    void mouseDragged(int x, int y, int button); // ���콺�� �巡���� �� ȣ��Ǵ� �Լ�
    void mouseReleased(int x, int y, int button); // ���콺 ��ư�� �� �� ȣ��Ǵ� �Լ�
    void checkPairs(); // ���� ���� Ȯ���ϴ� �Լ�
    void fillGrid(); // �׸��带 ä��� �Լ�
    bool isValidPair(int x1, int y1, int x2, int y2); // ��ȿ�� ������ Ȯ���ϴ� �Լ�
    bool isOverlapping(int x, int y, int w, int h, int x1, int y1, int x2, int y2); // ���ڵ��� ��ġ���� Ȯ���ϴ� �Լ�
    void drawModeSelection();
    void drawGame();
    void setupGame();
    const int gridSize = 10; // �׸����� ũ��
    const int cellSize = 40; // �� ���� ũ��
    const int maxNumber = 9; // ���� ���� �ִ� ����
    int grid[10][10]; // ���ڸ� �����ϴ� �׸���
    int score; // ����
    float timer; // ���� �ð�
    const float timeLimit = 30.0f; // ���� �ð�
    int mode;//���� ���
    bool drawingBox; // ���ڰ� �׷����� �ִ��� ����
    ofPoint startPoint, endPoint; // ������ �������� ����

    std::vector<std::pair<int, int>> getValidPairs(); // ��ȿ�� ���� ���� ��ȯ�ϴ� �Լ�
};
