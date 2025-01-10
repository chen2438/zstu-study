using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace Game2048 {
    public partial class Form1 : Form {
        public Form1() {
            InitializeComponent();
        }

        const int N = 4;  //方块在纵向及横向上的个数
        private int[,] board; //记录每个方块上的数
        Button[] btns;
        private int score;

        int gameMode;
        string[] str1 = { "夏", "商", "周", "秦", "汉", "隋", "唐", "宋", "元", "明", "清" };
        string[] str2 = { "一品", "二品", "三品", "四品", "五品", "六品", "七品", "八品", "九品", "良民", "贱民" };
        string[] str3 = { "士兵", "排长", "连长", "营长", "旅长", "师长", "军长", "司令", "大帅", "良民", "贱民" };


        private void Form1_Load(object sender, EventArgs e) {
            board = new int[N, N];
            score = 0;
            gameMode = 0;

            this.Text = "Game2048";
            this.DoubleBuffered = true;

            StartGame();
        }
        private void StartGame() {
            //设置两个不同的块为随机的2或4
            Random rnd = new Random();
            int n1 = rnd.Next(N * N);
            int n2;
            do {
                n2 = rnd.Next(N * N);
            }
            while (n1 == n2);
            board[n1 / N, n1 % N] = rnd.Next(2) * 2 + 2; //设为2或4
            board[n2 / N, n2 % N] = rnd.Next(2) * 2 + 2;

            InitialUI();
        }

        //初始化界面
        private void InitialUI() {
            //生成按钮
            GenerateAllButtons();

        }


        //产生所有的按钮
        private void GenerateAllButtons() {
            btns = new Button[N * N];

            int x0 = 5, y0 = 5, w = 60, d = w + 5;

            for (int i = 0; i < btns.Length; i++) {
                Button btn = new Button();

                int r = i / N;  //行
                int c = i % N;  //列

                btn.Left = x0 + c * d;
                btn.Top = y0 + r * d;
                btn.Width = w;
                btn.Height = w;
                btn.Font = new Font("楷体", 16);

                btn.Text = GetTextOfButton(board[r, c]);
                btn.BackColor = GetColorOfButton(board[r, c]);

                btn.Visible = true;
                btns[i] = btn;
                this.pnlBoard.Controls.Add(btn);
            }
        }

        //更新界面
        private void RefreshUI() {
            RefreshAllButtons();
        }
        private void RefreshAllButtons() {
            for (int i = 0; i < btns.Length; i++) {
                int r = i / N;  //行
                int c = i % N;  //列
                btns[i].Text = GetTextOfButton(board[r, c]);
                btns[i].BackColor = GetColorOfButton(board[r, c]);
            }
        }

        //得到方块上应有的文字
        string GetTextOfButton(int n) {
            if (n < 2) return "";

            int k = (int)Math.Log(n, 2) - 1;

            if (gameMode == 0) {
                return n.ToString();
            } else if (gameMode == 1) {
                return str1[k];
            } else if (gameMode == 2) {
                return str2[k];
            }
            return "";
        }

        //得到方块上应有的颜色

        Color GetColorOfButton(int n) {
            if (n == 0) return Color.FromArgb(100, 200, 200, 200);

            int tmp = 230 - (int)Math.Log(n, 2) * 20;
            return Color.FromArgb(250, tmp, tmp, 0);
        }


        //处理键盘消息
        //要注意的是:由于按钮等元素的存在,窗体得不到KeyDown事件,所以在覆盖ProcessCmdKey
        protected override bool ProcessCmdKey(ref Message msg, Keys keyData) {
            bool bMoved = false;

            if (keyData == Keys.Right) {
                bMoved = rightMove();
            } else if (keyData == Keys.Left) {
                bMoved = leftMove();
            } else if (keyData == Keys.Down) {
                bMoved = downMove();
            } else if (keyData == Keys.Up) {
                bMoved = upMove();
            }

            if (bMoved) {
                generateNewData();
                RefreshUI();
                if (IsGameOver() == true)
                    MessageBox.Show("Game Over!");
                return true;
            }

            return base.ProcessCmdKey(ref msg, keyData);
        }

        //产生新的随机数据
        private void generateNewData() {
            Random rnd = new Random();
            //随机找到一个空的块
            int nCount;
            do {
                nCount = rnd.Next(N * N);
            }
            while (board[nCount / N, nCount % N] != 0);

            board[nCount / N, nCount % N] = rnd.Next(2) * 2 + 2; //其值设为2或者4
        }

        #region 关于四个方向的业务逻辑
        private bool rightMove() {
            bool isMoved = false;
            for (int j = 0; j < board.GetLength(0); j++) //针对所有的行
            {
                int x1 = -1, y1 = -1, value1 = -1;// x2=-1, y2=-1,value2=-1;
                for (int i = board.GetLength(1) - 1; i > -1; i--) //从右边起，针对每个块进行处理
                {
                    if (board[j, i] == 0) continue; //空的块不处理
                    if (board[j, i] == value1)//如果与上一次找到的相等，则合并
                    {
                        board[x1, y1] = board[x1, y1] * 2;
                        board[j, i] = 0;
                        value1 = -1;
                        score += board[x1, y1];
                        isMoved = true;
                    } else {
                        int k;
                        for (k = i + 1; k < board.GetLength(1); k++) //向右找到一个非空的块
                        {
                            if (board[j, k] > 0)
                                break;
                        }
                        if (k - 1 != i)//如果这个非空的块左边有空位置
                        {
                            isMoved = true;
                            board[j, k - 1] = board[j, i]; //“移动”到这里（将其上的数字显示到这里）
                            board[j, i] = 0;
                        }
                        value1 = board[j, k - 1]; //记下这个值（非空的块）
                        x1 = j;
                        y1 = k - 1;
                    }
                }
            }
            return isMoved;
        }
        private bool upMove() {
            bool isMoved = false;
            for (int i = 0; i < board.GetLength(1); i++) {
                int x1 = -1, y1 = -1, value1 = -1;// x2=-1, y2=-1,value2=-1;
                for (int j = 0; j < board.GetLength(0); j++) {
                    if (board[j, i] != 0) {
                        if (value1 < 0) {
                            int k;
                            for (k = j - 1; k > -1; k--) {
                                if (board[k, i] > 0)
                                    break;
                            }
                            board[k + 1, i] = board[j, i];
                            if (k + 1 != j) {
                                board[j, i] = 0;
                                isMoved = true;
                            }
                            value1 = board[k + 1, i];
                            x1 = k + 1;
                            y1 = i;
                        } else {
                            if (board[j, i] == value1)//合并
                            {
                                board[x1, y1] = board[x1, y1] * 2;
                                board[j, i] = 0;
                                value1 = -1;
                                score += board[x1, y1];
                                isMoved = true;
                            } else {
                                int k;
                                for (k = j - 1; k > -1; k--) {
                                    if (board[k, i] > 0)
                                        break;
                                }
                                board[k + 1, i] = board[j, i];
                                if (k + 1 != j) {
                                    isMoved = true;
                                    board[j, i] = 0;
                                }
                                value1 = board[k + 1, i];
                                x1 = k + 1;
                                y1 = i;
                            }
                        }
                    }
                }

            }
            return isMoved;
        }

        private bool leftMove() {
            bool isMoved = false;
            for (int j = 0; j < board.GetLength(0); j++) {
                int x1 = -1, y1 = -1, value1 = -1;// x2=-1, y2=-1,value2=-1;
                for (int i = 0; i < board.GetLength(1); i++) {
                    if (board[j, i] != 0) {
                        if (value1 < 0) {
                            int k;
                            for (k = i - 1; k > -1; k--) {
                                if (board[j, k] > 0)
                                    break;
                            }
                            board[j, k + 1] = board[j, i];
                            if (k + 1 != i) {
                                isMoved = true;
                                board[j, i] = 0;
                            }
                            value1 = board[j, k + 1];
                            x1 = j;
                            y1 = k + 1;
                        } else {
                            if (board[j, i] == value1)//合并
                            {
                                board[x1, y1] = board[x1, y1] * 2;
                                board[j, i] = 0;
                                value1 = -1;
                                score += board[x1, y1];
                                isMoved = true;
                            } else {
                                int k;
                                for (k = i - 1; k > -1; k--) {
                                    if (board[j, k] > 0)
                                        break;
                                }
                                board[j, k + 1] = board[j, i];
                                if (k + 1 != i) {
                                    isMoved = true;
                                    board[j, i] = 0;
                                }
                                value1 = board[j, k + 1];
                                x1 = j;
                                y1 = k + 1;
                            }
                        }
                    }
                }

            }
            return isMoved;
        }



        private bool downMove() {
            bool isMoved = false;
            for (int i = 0; i < board.GetLength(1); i++) {
                int x1 = -1, y1 = -1, value1 = -1;// x2=-1, y2=-1,value2=-1;
                for (int j = board.GetLength(0) - 1; j > -1; j--) {
                    if (board[j, i] != 0) {
                        if (value1 < 0) {
                            int k;
                            for (k = j + 1; k < board.GetLength(0); k++) {
                                if (board[k, i] > 0)
                                    break;
                            }
                            board[k - 1, i] = board[j, i];
                            if (k - 1 != j) {
                                board[j, i] = 0;
                                isMoved = true;
                            }
                            value1 = board[k - 1, i];
                            x1 = k - 1;
                            y1 = i;
                        } else {
                            if (board[j, i] == value1)//合并
                            {
                                board[x1, y1] = board[x1, y1] * 2;
                                board[j, i] = 0;
                                value1 = -1;
                                score += board[x1, y1];
                                isMoved = true;
                            } else {
                                int k;
                                for (k = j + 1; k < board.GetLength(0); k++) {
                                    if (board[k, i] > 0)
                                        break;
                                }
                                board[k - 1, i] = board[j, i];
                                if (k - 1 != j) {
                                    board[j, i] = 0;
                                    isMoved = true;
                                }
                                value1 = board[k - 1, i];
                                x1 = k - 1;
                                y1 = i;
                            }
                        }
                    }
                }

            }
            return isMoved;
        }

        #endregion

        private bool IsGameOver() {
            int nCount = 0; //计算非空的格子的个数
            for (int i = 0; i < board.GetLength(0); i++) {
                for (int j = 0; j < board.GetLength(1); j++) {
                    if (board[i, j] > 0) nCount++;
                }
            }
            if (nCount != N * N) return false;

            //如果满了，并且没有可以相邻相同（可合并），则GameOver
            for (int i = 0; i < board.GetLength(0) - 1; i++) {
                for (int j = 0; j < board.GetLength(1) - 1; j++) {
                    if (board[i, j] == 0) continue;
                    if (board[i, j] == board[i + 1, j] || board[i, j] == board[i, j + 1])
                        return false;
                }
            }
            return true;
        }

    }

}