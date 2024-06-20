#include "ofApp.h"

// �ʱ� ���� �Լ�
void ofApp::setup() {
    ofSetFrameRate(60); // ������ ����Ʈ ����
    ofBackground(255); // ��� ���� ���� (���)
    score = 0; // �ʱ� ���� ����
    timer = timeLimit; // Ÿ�̸� �ʱ� ����
    drawingBox = false; // ���� �׸��� ���� �ʱ�ȭ
    mode = 0; // �⺻ ��� ���� (0�� ��� ���� ȭ���� �ǹ�)
}

// �� �����Ӹ��� ȣ��Ǵ� ������Ʈ �Լ�
void ofApp::update() {
    if (mode != 0 && timer > 0) { // Ÿ�̸Ӱ� 0���� ũ�� ��尡 ���õ� ���
        timer -= ofGetLastFrameTime(); // ���� �������� �ð��� Ÿ�̸ӿ��� ����
    }
    else if (timer <= 0) {
        timer = 0; // Ÿ�̸Ӹ� 0���� ����
    }
}

// ȭ�鿡 �׸��� �Լ�
void ofApp::draw() {
    if (mode == 0) {
        drawModeSelection(); // ��� ���� ȭ�� �׸���
    }
    else {
        drawGame(); // ���� ȭ�� �׸���
    }
}

// ��� ���� ȭ�� �׸��� �Լ�
void ofApp::drawModeSelection() {
    ofSetColor(0);
    std::string selectModeMsg = "Select Game Mode\n1. Mode 1: Pairs summing to 10\n2. Mode 2: Even random distribution";
    ofDrawBitmapStringHighlight(selectModeMsg, ofGetWidth() / 2 - 150, ofGetHeight() / 2, ofColor::white, ofColor::black);
}

// ���� ȭ�� �׸��� �Լ�
void ofApp::drawGame() {
    // �׸����� ��� ���� �׸���
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            int x = i * cellSize; // ���� x ��ǥ
            int y = j * cellSize; // ���� y ��ǥ
            ofSetColor(200); // �� ���� ����
            ofDrawRectangle(x, y, cellSize, cellSize); // �� �׸���
            if (grid[i][j] != -1) { // ���� ������� ������
                ofSetColor(0); // �ؽ�Ʈ ���� ����
                ofDrawBitmapString(ofToString(grid[i][j]), x + cellSize / 2, y + cellSize / 2); // �� ���� �׸���
            }
        }
    }
    // ������ Ÿ�̸Ӹ� ȭ�鿡 �׸���
    ofSetColor(0);
    ofDrawBitmapString("Score: " + ofToString(score), 10, gridSize * cellSize + 20); // ���� �׸���
    ofDrawBitmapString("Time: " + ofToString(timer, 2), 10, gridSize * cellSize + 40); // Ÿ�̸� �׸���

    // Ÿ�̸Ӱ� 0�� �Ǹ� ���� ���� �޽��� �׸���
    if (timer == 0) {
        std::string gameOverMsg = "Game Over\nScore: " + ofToString(score); // ���� ���� �޽��� ����
        ofDrawBitmapStringHighlight(gameOverMsg, ofGetWidth() / 2 - 50, ofGetHeight() / 2, ofColor::white, ofColor::black); // ���� ���� �޽��� �׸���
    }

    // ���ڰ� �׷����� ������ ���� �׸���
    if (drawingBox) {
        ofSetColor(0, 0, 255, 100); // ���� ���� ����
        ofDrawRectangle(startPoint.x, startPoint.y, endPoint.x - startPoint.x, endPoint.y - startPoint.y); // ���� �׸���
    }
}

// Ű�� ������ �� ȣ��Ǵ� �Լ�
void ofApp::keyPressed(int key) {
    if (mode == 0) { // ��� ���� ȭ�鿡��
        if (key == '1') {
            mode = 1; // ��� 1 ����
            setupGame(); // ���� ����
        }
        else if (key == '2') {
            mode = 2; // ��� 2 ����
            setupGame(); // ���� ����
        }
    }
}

// ���� ���� �Լ�
void ofApp::setupGame() {
    score = 0; // ���� �ʱ�ȭ
    timer = timeLimit; // Ÿ�̸� �ʱ�ȭ
    drawingBox = false; // ���� �׸��� ���� �ʱ�ȭ
    fillGrid(); // �׸��� ä���
}

// ���콺 ��ư�� ������ �� ȣ��Ǵ� �Լ�
void ofApp::mousePressed(int x, int y, int button) {
    if (timer == 0) return; // Ÿ�̸Ӱ� 0�̸� ��ȯ

    startPoint.set(x, y); // ���� ������ ����
    endPoint.set(x, y); // ���� ���� �ʱ�ȭ
    drawingBox = true; // ���� �׸��� ���� ����
}

// ���콺�� �巡���� �� ȣ��Ǵ� �Լ�
void ofApp::mouseDragged(int x, int y, int button) {
    if (timer == 0) return; // Ÿ�̸Ӱ� 0�̸� ��ȯ

    endPoint.set(x, y); // ���� ���� ������Ʈ
}

// ���콺 ��ư�� �� �� ȣ��Ǵ� �Լ�
void ofApp::mouseReleased(int x, int y, int button) {
    if (timer == 0) return; // Ÿ�̸Ӱ� 0�̸� ��ȯ

    drawingBox = false; // ���� �׸��� ���� ����

    int sum = 0; // ���õ� ������ �հ�
    std::vector<std::pair<int, int>> cellsToClear; // ���� �� ���

    // �׸����� ��� ���� �˻��Ͽ� ���ڿ� ��ġ�� �� ã��
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            int cellX = i * cellSize; // ���� x ��ǥ
            int cellY = j * cellSize; // ���� y ��ǥ
            if (isOverlapping(cellX, cellY, cellSize, cellSize, startPoint.x, startPoint.y, endPoint.x, endPoint.y) && grid[i][j] != -1) { // ���� ���ڰ� ��ġ��
                sum += grid[i][j]; // ���� ���ڸ� �հ迡 �߰�
                cellsToClear.push_back({ i, j }); // ���� �� ��Ͽ� �߰�
            }
        }
    }

    // ���õ� ������ ���� 10�̸� �� ����
    if (sum == 10) {
        for (auto& cell : cellsToClear) {
            grid[cell.first][cell.second] = -1; // �� ����
        }
        score++; // ���� ����
    }
}

// ��ȿ�� ������ Ȯ���ϴ� �Լ�
bool ofApp::isValidPair(int x1, int y1, int x2, int y2) {
    if ((abs(x1 - x2) <= 1 && abs(y1 - y2) <= 1) && (grid[x1][y1] + grid[x2][y2] == 10)) { // �����ϰ� ���� 10�̸�
        return true; // ��ȿ�� ��
    }
    return false; // ��ȿ���� ���� ��
}

// ���ڵ��� ��ġ���� Ȯ���ϴ� �Լ�
bool ofApp::isOverlapping(int x, int y, int w, int h, int x1, int y1, int x2, int y2) {
    int minX = std::min(x1, x2); // ������ �ּ� x ��ǥ
    int maxX = std::max(x1, x2); // ������ �ִ� x ��ǥ
    int minY = std::min(y1, y2); // ������ �ּ� y ��ǥ
    int maxY = std::max(y1, y2); // ������ �ִ� y ��ǥ

    return (x < maxX && x + w > minX && y < maxY && y + h > minY); // ���ڰ� ��ġ���� ���� ��ȯ
}

// ��ȿ�� ���� ���� ��ȯ�ϴ� �Լ�
std::vector<std::pair<int, int>> ofApp::getValidPairs() {
    return { {1, 9}, {2, 8}, {3, 7}, {4, 6}, {5, 5} }; // ��ȿ�� ���� ��
}

// �׸��带 ä��� �Լ�
void ofApp::fillGrid() {
    std::vector<std::pair<int, int>> pairs = getValidPairs(); // ��ȿ�� ���� �� ��������
    std::random_device rd; // ���� ��ġ ����
    std::mt19937 g(rd()); // ���� ������ �ʱ�ȭ

    // �׸��带 �ʱ�ȭ
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            grid[i][j] = -1; // �׸��� ���� -1�� �ʱ�ȭ
        }
    }

    // �׸��忡 ���� ���� ä��� (��忡 ���� �ٸ�)
    if (mode == 1) {
        // ��� 1: ���� 10�� ¦��� ä���
        for (int i = 0; i < gridSize; i++) {
            for (int j = 0; j < gridSize; j++) {
                if (grid[i][j] == -1) { // �׸��� ���� ���������
                    // ���� ���� �� ����
                    std::pair<int, int> pair = pairs[std::uniform_int_distribution<int>(0, pairs.size() - 1)(g)];
                    grid[i][j] = pair.first; // ù ��° ���� ��ġ

                    // ������ ����� ����
                    std::vector<std::pair<int, int>> directions = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };
                    std::shuffle(directions.begin(), directions.end(), g); // ������ �������� ����

                    bool placed = false; // ���ڰ� ��ġ�Ǿ����� ����
                    // ���� ��ġ �õ�
                    for (auto& dir : directions) {
                        int ni = i + dir.first; // ���� ���� x ��ǥ
                        int nj = j + dir.second; // ���� ���� y ��ǥ

                        // ���� ���� �׸��� ���� ���� �ְ� ���������
                        if (ni >= 0 && ni < gridSize && nj >= 0 && nj < gridSize && grid[ni][nj] == -1) {
                            grid[ni][nj] = pair.second; // �� ��° ���� ��ġ
                            placed = true; // ��ġ �Ϸ�
                            break;
                        }
                    }

                    // ������ ���� ��ġ���� ���� ���, �׸��� ��ü�� �ٽ� �˻��Ͽ� ��ġ
                    if (!placed) {
                        for (int ni = 0; ni < gridSize; ni++) {
                            for (int nj = 0; nj < gridSize; nj++) {
                                if (grid[ni][nj] == -1) {
                                    grid[ni][nj] = pair.second; // �� ��° ���� ��ġ
                                    placed = true; // ��ġ �Ϸ�
                                    break;
                                }
                            }
                            if (placed) break;
                        }
                    }
                }
            }
        }
    }
    else if (mode == 2) {
        // ��� 2: ���ڵ��� �յ��ϰ� �����ϰ� ������Ű��
        std::vector<int> numbers;
        int totalCells = gridSize * gridSize;
        int repeatCount = totalCells / 9; // �� ���ڰ� �ݺ��Ǵ� Ƚ��
        for (int n = 1; n <= 9; ++n) {
            for (int i = 0; i < repeatCount; ++i) {
                numbers.push_back(n);
            }
        }

        // ���� �׸��� �� ���� 9�� ����� �ƴ϶�� ������ ���� �߰��� ä��
        for (int i = numbers.size(); i < totalCells; ++i) {
            numbers.push_back(1 + (i % 9)); // 1���� 9���� �ݺ��Ͽ� �߰�
        }

        std::shuffle(numbers.begin(), numbers.end(), g);

        int index = 0;
        for (int i = 0; i < gridSize; i++) {
            for (int j = 0; j < gridSize; j++) {
                grid[i][j] = numbers[index++];
            }
        }
    }
}