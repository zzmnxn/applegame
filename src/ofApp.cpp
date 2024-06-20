#include "ofApp.h"

// 초기 설정 함수
void ofApp::setup() {
    ofSetFrameRate(60); // 프레임 레이트 설정
    ofBackground(255); // 배경 색상 설정 (흰색)
    score = 0; // 초기 점수 설정
    timer = timeLimit; // 타이머 초기 설정
    drawingBox = false; // 상자 그리기 상태 초기화
    mode = 0; // 기본 모드 설정 (0은 모드 선택 화면을 의미)
}

// 매 프레임마다 호출되는 업데이트 함수
void ofApp::update() {
    if (mode != 0 && timer > 0) { // 타이머가 0보다 크고 모드가 선택된 경우
        timer -= ofGetLastFrameTime(); // 지난 프레임의 시간을 타이머에서 빼기
    }
    else if (timer <= 0) {
        timer = 0; // 타이머를 0으로 설정
    }
}

// 화면에 그리기 함수
void ofApp::draw() {
    if (mode == 0) {
        drawModeSelection(); // 모드 선택 화면 그리기
    }
    else {
        drawGame(); // 게임 화면 그리기
    }
}

// 모드 선택 화면 그리기 함수
void ofApp::drawModeSelection() {
    ofSetColor(0);
    std::string selectModeMsg = "Select Game Mode\n1. Mode 1: Pairs summing to 10\n2. Mode 2: Even random distribution";
    ofDrawBitmapStringHighlight(selectModeMsg, ofGetWidth() / 2 - 150, ofGetHeight() / 2, ofColor::white, ofColor::black);
}

// 게임 화면 그리기 함수
void ofApp::drawGame() {
    // 그리드의 모든 셀을 그리기
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            int x = i * cellSize; // 셀의 x 좌표
            int y = j * cellSize; // 셀의 y 좌표
            ofSetColor(200); // 셀 색상 설정
            ofDrawRectangle(x, y, cellSize, cellSize); // 셀 그리기
            if (grid[i][j] != -1) { // 셀이 비어있지 않으면
                ofSetColor(0); // 텍스트 색상 설정
                ofDrawBitmapString(ofToString(grid[i][j]), x + cellSize / 2, y + cellSize / 2); // 셀 숫자 그리기
            }
        }
    }
    // 점수와 타이머를 화면에 그리기
    ofSetColor(0);
    ofDrawBitmapString("Score: " + ofToString(score), 10, gridSize * cellSize + 20); // 점수 그리기
    ofDrawBitmapString("Time: " + ofToString(timer, 2), 10, gridSize * cellSize + 40); // 타이머 그리기

    // 타이머가 0이 되면 게임 오버 메시지 그리기
    if (timer == 0) {
        std::string gameOverMsg = "Game Over\nScore: " + ofToString(score); // 게임 오버 메시지 생성
        ofDrawBitmapStringHighlight(gameOverMsg, ofGetWidth() / 2 - 50, ofGetHeight() / 2, ofColor::white, ofColor::black); // 게임 오버 메시지 그리기
    }

    // 상자가 그려지고 있으면 상자 그리기
    if (drawingBox) {
        ofSetColor(0, 0, 255, 100); // 상자 색상 설정
        ofDrawRectangle(startPoint.x, startPoint.y, endPoint.x - startPoint.x, endPoint.y - startPoint.y); // 상자 그리기
    }
}

// 키를 눌렀을 때 호출되는 함수
void ofApp::keyPressed(int key) {
    if (mode == 0) { // 모드 선택 화면에서
        if (key == '1') {
            mode = 1; // 모드 1 선택
            setupGame(); // 게임 설정
        }
        else if (key == '2') {
            mode = 2; // 모드 2 선택
            setupGame(); // 게임 설정
        }
    }
}

// 게임 설정 함수
void ofApp::setupGame() {
    score = 0; // 점수 초기화
    timer = timeLimit; // 타이머 초기화
    drawingBox = false; // 상자 그리기 상태 초기화
    fillGrid(); // 그리드 채우기
}

// 마우스 버튼을 눌렀을 때 호출되는 함수
void ofApp::mousePressed(int x, int y, int button) {
    if (timer == 0) return; // 타이머가 0이면 반환

    startPoint.set(x, y); // 상자 시작점 설정
    endPoint.set(x, y); // 상자 끝점 초기화
    drawingBox = true; // 상자 그리기 상태 설정
}

// 마우스를 드래그할 때 호출되는 함수
void ofApp::mouseDragged(int x, int y, int button) {
    if (timer == 0) return; // 타이머가 0이면 반환

    endPoint.set(x, y); // 상자 끝점 업데이트
}

// 마우스 버튼을 뗄 때 호출되는 함수
void ofApp::mouseReleased(int x, int y, int button) {
    if (timer == 0) return; // 타이머가 0이면 반환

    drawingBox = false; // 상자 그리기 상태 해제

    int sum = 0; // 선택된 숫자의 합계
    std::vector<std::pair<int, int>> cellsToClear; // 지울 셀 목록

    // 그리드의 모든 셀을 검사하여 상자와 겹치는 셀 찾기
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            int cellX = i * cellSize; // 셀의 x 좌표
            int cellY = j * cellSize; // 셀의 y 좌표
            if (isOverlapping(cellX, cellY, cellSize, cellSize, startPoint.x, startPoint.y, endPoint.x, endPoint.y) && grid[i][j] != -1) { // 셀과 상자가 겹치면
                sum += grid[i][j]; // 셀의 숫자를 합계에 추가
                cellsToClear.push_back({ i, j }); // 지울 셀 목록에 추가
            }
        }
    }

    // 선택된 숫자의 합이 10이면 셀 비우기
    if (sum == 10) {
        for (auto& cell : cellsToClear) {
            grid[cell.first][cell.second] = -1; // 셀 비우기
        }
        score++; // 점수 증가
    }
}

// 유효한 쌍인지 확인하는 함수
bool ofApp::isValidPair(int x1, int y1, int x2, int y2) {
    if ((abs(x1 - x2) <= 1 && abs(y1 - y2) <= 1) && (grid[x1][y1] + grid[x2][y2] == 10)) { // 인접하고 합이 10이면
        return true; // 유효한 쌍
    }
    return false; // 유효하지 않은 쌍
}

// 상자들이 겹치는지 확인하는 함수
bool ofApp::isOverlapping(int x, int y, int w, int h, int x1, int y1, int x2, int y2) {
    int minX = std::min(x1, x2); // 상자의 최소 x 좌표
    int maxX = std::max(x1, x2); // 상자의 최대 x 좌표
    int minY = std::min(y1, y2); // 상자의 최소 y 좌표
    int maxY = std::max(y1, y2); // 상자의 최대 y 좌표

    return (x < maxX && x + w > minX && y < maxY && y + h > minY); // 상자가 겹치는지 여부 반환
}

// 유효한 숫자 쌍을 반환하는 함수
std::vector<std::pair<int, int>> ofApp::getValidPairs() {
    return { {1, 9}, {2, 8}, {3, 7}, {4, 6}, {5, 5} }; // 유효한 숫자 쌍
}

// 그리드를 채우는 함수
void ofApp::fillGrid() {
    std::vector<std::pair<int, int>> pairs = getValidPairs(); // 유효한 숫자 쌍 가져오기
    std::random_device rd; // 랜덤 장치 생성
    std::mt19937 g(rd()); // 난수 생성기 초기화

    // 그리드를 초기화
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            grid[i][j] = -1; // 그리드 셀을 -1로 초기화
        }
    }

    // 그리드에 숫자 쌍을 채우기 (모드에 따라 다름)
    if (mode == 1) {
        // 모드 1: 합이 10인 짝들로 채우기
        for (int i = 0; i < gridSize; i++) {
            for (int j = 0; j < gridSize; j++) {
                if (grid[i][j] == -1) { // 그리드 셀이 비어있으면
                    // 랜덤 숫자 쌍 선택
                    std::pair<int, int> pair = pairs[std::uniform_int_distribution<int>(0, pairs.size() - 1)(g)];
                    grid[i][j] = pair.first; // 첫 번째 숫자 배치

                    // 인접한 방향들 정의
                    std::vector<std::pair<int, int>> directions = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };
                    std::shuffle(directions.begin(), directions.end(), g); // 방향을 랜덤으로 섞기

                    bool placed = false; // 숫자가 배치되었는지 여부
                    // 숫자 배치 시도
                    for (auto& dir : directions) {
                        int ni = i + dir.first; // 인접 셀의 x 좌표
                        int nj = j + dir.second; // 인접 셀의 y 좌표

                        // 인접 셀이 그리드 범위 내에 있고 비어있으면
                        if (ni >= 0 && ni < gridSize && nj >= 0 && nj < gridSize && grid[ni][nj] == -1) {
                            grid[ni][nj] = pair.second; // 두 번째 숫자 배치
                            placed = true; // 배치 완료
                            break;
                        }
                    }

                    // 인접한 셀에 배치하지 못한 경우, 그리드 전체를 다시 검사하여 배치
                    if (!placed) {
                        for (int ni = 0; ni < gridSize; ni++) {
                            for (int nj = 0; nj < gridSize; nj++) {
                                if (grid[ni][nj] == -1) {
                                    grid[ni][nj] = pair.second; // 두 번째 숫자 배치
                                    placed = true; // 배치 완료
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
        // 모드 2: 숫자들을 균등하게 랜덤하게 분포시키기
        std::vector<int> numbers;
        int totalCells = gridSize * gridSize;
        int repeatCount = totalCells / 9; // 각 숫자가 반복되는 횟수
        for (int n = 1; n <= 9; ++n) {
            for (int i = 0; i < repeatCount; ++i) {
                numbers.push_back(n);
            }
        }

        // 만약 그리드 셀 수가 9의 배수가 아니라면 나머지 셀을 추가로 채움
        for (int i = numbers.size(); i < totalCells; ++i) {
            numbers.push_back(1 + (i % 9)); // 1부터 9까지 반복하여 추가
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