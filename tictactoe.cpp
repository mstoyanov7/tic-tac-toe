#include <ncursed.h>
#include <array>

const int ROWS = 3;
const int COLUMNS = 3;

int main() {
  initscr();
  noecho();
  curs_set(0);

  std::array<std::array<char, COLUMNS>, ROWS> board;
  board.fill({' ', ' ', ' '});

  int current_player = 1;
  while (true) {
    clear();

    // Draw board
    for (int i = 0; i < ROWS; i++) {
      for (int j = 0; j < COLUMNS; j++) {
        mvaddch(i, j * 2, '|');
        mvaddch(i, j * 2 + 1, board[i][j]);
      }
      mvaddch(i, COLUMNS * 2, '|');
    }
    for (int i = 0; i < COLUMNS * 2 + 1; i++) {
      mvaddch(ROWS, i, '-');
    }

    // Get user input
    int row, column;
    mvprintw(ROWS + 1, 0, "Player %d's turn. Enter row and column: ", current_player);
    scanw("%d%d", &row, &column);
    row--;
    column--;

    // Update board
    if (row >= 0 && row < ROWS && column >= 0 && column < COLUMNS && board[row][column] == ' ') {
      board[row][column] = (current_player == 1) ? 'X' : 'O';
      current_player = (current_player == 1) ? 2 : 1;
    }

    // Check if game is over
    bool game_over = false;
    for (int i = 0; i < ROWS; i++) {
      if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
        game_over = true;
        break;
      }
    }
    for (int i = 0; i < COLUMNS; i++) {
      if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
        game_over = true;
        break;
      }
    }
    if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
      game_over = true;
    }
    if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
      game_over = true;
    }
    if (game_over) {
      break;
    }
  }

  clear();
  mvprintw(ROWS / 2, COLUMNS - COLUMNS / 2, "Game Over!");
  refresh
