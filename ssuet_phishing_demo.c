#include "raylib.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define MAX_INPUT 50
#define MAX_USERS 50

typedef enum { SCR_WELCOME, SCR_REGISTER, SCR_LOGIN, SCR_LOADING, SCR_PORTAL } Screen;
typedef enum { TAB_DASH, TAB_COURSES, TAB_GRADES, TAB_ATTEND, TAB_FEES, TAB_SCHED } Tab;

typedef struct {
    char id[MAX_INPUT], email[MAX_INPUT], pass[MAX_INPUT];
} User;

typedef struct {
    char id[MAX_INPUT], email[MAX_INPUT], pass[MAX_INPUT];
    bool idA, emailA, passA;
    int idLen, emailLen, passLen;
    Screen scr;
    Tab tab;
} Form;

User users[MAX_USERS];
int userCount = 0;
float loadProg = 0, fade = 0;
char msg[100] = "";
float msgTimer = 0;

void RegUser(const char *id, const char *em, const char *pw) {
    if (userCount < MAX_USERS) {
        strcpy(users[userCount].id, id);
        strcpy(users[userCount].email, em);
        strcpy(users[userCount++].pass, pw);
    }
}

bool CheckUser(const char *id, const char *em, const char *pw) {
    for (int i = 0; i < userCount; i++)
        if (!strcmp(users[i].id, id) && !strcmp(users[i].email, em) && !strcmp(users[i].pass, pw))
            return true;
    return false;
}

bool UserExists(const char *id) {
    for (int i = 0; i < userCount; i++)
        if (!strcmp(users[i].id, id)) return true;
    return false;
}

void SaveLog(const char *id, const char *em, const char *pw, bool phish) {
    FILE *f = fopen(phish ? "phishing.txt" : "legitimate.txt", "a");
    if (f) {
        time_t t = time(NULL);
        fprintf(f, "\n=== %s ===\nTime: %sID: %s\nEmail: %s\nPass: %s\n", 
                phish ? "PHISH" : "LEGIT", ctime(&t), id, em, pw);
        fclose(f);
    }
}

void Btn(Rectangle r, const char *t, Color c, bool *clk) {
    bool hov = CheckCollisionPointRec(GetMousePosition(), r);
    DrawRectangleRounded(r, 0.3f, 10, hov ? ColorBrightness(c, 0.2f) : c);
    DrawText(t, r.x + (r.width - MeasureText(t, 22)) / 2, r.y + 17, 22, WHITE);
    if (hov && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) *clk = true;
}

void Input(Rectangle r, const char *lbl, char *txt, int len, bool *act, bool pwd) {
    bool hov = CheckCollisionPointRec(GetMousePosition(), r);
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) *act = hov;
    DrawRectangleRounded(r, 0.15f, 10, (Color){31, 42, 58, 255});
    DrawRectangleRoundedLinesEx(r, 0.15f, 10, *act ? 3 : 2, *act ? GREEN : (hov ? Fade(GREEN, 0.5f) : Fade(WHITE, 0.3f)));
    DrawText(lbl, r.x, r.y - 22, 13, WHITE);
    
    if (len > 0) {
        if (pwd) {
            char m[MAX_INPUT];
            memset(m, '*', len);
            m[len] = 0;
            DrawText(m, r.x + 12, r.y + 16, 18, WHITE);
        } else DrawText(txt, r.x + 12, r.y + 16, 18, WHITE);
    } else DrawText(lbl, r.x + 12, r.y + 16, 18, Fade(GRAY, 0.5f));
    
    if (*act && ((int)(GetTime() * 2) % 2)) 
        DrawRectangle(r.x + 12 + MeasureText(txt, 18), r.y + 16, 2, 18, GREEN);
}

void Handle(char *t, int *l, bool act) {
    if (!act) return;
    int k = GetCharPressed();
    while (k > 0) {
        if (k >= 32 && k <= 125 && *l < MAX_INPUT - 1) t[(*l)++] = k, t[*l] = 0;
        k = GetCharPressed();
    }
    if (IsKeyPressed(KEY_BACKSPACE) && *l > 0) t[--(*l)] = 0;
}

void DrawTab(int x, int y, int w, Tab t) {
    switch(t) {
        case TAB_DASH:
            DrawText("TODAY'S CLASSES", x, y, 18, DARKGRAY);
            DrawRectangle(x + 2, y + 32, w - 20, 122, Fade(BLACK, 0.1f));
            DrawRectangle(x, y + 30, w - 20, 120, WHITE);
            DrawRectangleLines(x, y + 30, w - 20, 120, GRAY);
            DrawText("08:00 - 09:30  Introduction to Programming Lab", x + 12, y + 42, 13, BLACK);
            DrawText("09:45 - 11:15  Calculus and Analytical Geometry", x + 12, y + 67, 13, BLACK);
            DrawText("11:30 - 01:00  Applied Physics", x + 12, y + 92, 13, BLACK);
            DrawText("02:00 - 03:30  Model Driven Development", x + 12, y + 117, 13, BLACK);
            
            DrawText("QUICK STATS", x, y + 170, 18, DARKGRAY);
            DrawRectangle(x + 2, y + 202, w - 20, 82, Fade(BLACK, 0.1f));
            DrawRectangle(x, y + 200, w - 20, 80, WHITE);
            DrawRectangleLines(x, y + 200, w - 20, 80, GRAY);
            DrawText("Overall Attendance:", x + 12, y + 212, 14, DARKGRAY);
            DrawText("85%", x + 180, y + 212, 14, GREEN);
            DrawText("CGPA:", x + 12, y + 237, 14, DARKGRAY);
            DrawText("3.45", x + 180, y + 237, 14, BLACK);
            DrawText("Credits Earned:", x + 12, y + 257, 14, DARKGRAY);
            DrawText("45/120", x + 180, y + 257, 14, BLACK);
            break;
            
        case TAB_COURSES:
            DrawText("ENROLLED COURSES - SEMESTER 1", x, y, 18, DARKGRAY);
            DrawRectangle(x + 2, y + 32, w - 20, 262, Fade(BLACK, 0.1f));
            DrawRectangle(x, y + 30, w - 20, 260, WHITE);
            DrawRectangleLines(x, y + 30, w - 20, 260, GRAY);
            
            DrawText("CS-101  Introduction to Programming", x + 12, y + 42, 13, BLACK);
            DrawText("Credits: 3  |  Instructor: Dr. Ahmed Khan", x + 22, y + 62, 11, GRAY);
            
            DrawText("MATH-102  Calculus & Analytical Geometry", x + 12, y + 92, 13, BLACK);
            DrawText("Credits: 3  |  Instructor: Dr. Sarah Ali", x + 22, y + 112, 11, GRAY);
            
            DrawText("PHY-103  Applied Physics", x + 12, y + 142, 13, BLACK);
            DrawText("Credits: 3  |  Instructor: Dr. Hassan Raza", x + 22, y + 162, 11, GRAY);
            
            DrawText("CS-104  Model Driven Development", x + 12, y + 192, 13, BLACK);
            DrawText("Credits: 3  |  Instructor: Dr. Ali Asghar", x + 22, y + 212, 11, GRAY);
            
            DrawText("ISL-101  Understanding of Quran-1", x + 12, y + 242, 13, BLACK);
            DrawText("Credits: 2  |  Instructor: Mufti Saeed Ahmed", x + 22, y + 262, 11, GRAY);
            break;
            
        case TAB_GRADES:
            DrawText("GRADE REPORT - SEMESTER 1", x, y, 18, DARKGRAY);
            DrawRectangle(x + 2, y + 32, w - 20, 202, Fade(BLACK, 0.1f));
            DrawRectangle(x, y + 30, w - 20, 200, WHITE);
            DrawRectangleLines(x, y + 30, w - 20, 200, GRAY);
            
            DrawText("Course                  Mid  Final Total Grade", x + 12, y + 42, 13, DARKGRAY);
            DrawLine(x + 12, y + 60, x + w - 32, y + 60, GRAY);
            
            DrawText("Programming             35   42    77    A-", x + 12, y + 72, 13, BLACK);
            DrawText("Calculus                28   38    66    B", x + 12, y + 97, 13, BLACK);
            DrawText("Physics                 40   45    85    A", x + 12, y + 122, 13, BLACK);
            DrawText("Model Driven Dev        32   40    72    B+", x + 12, y + 147, 13, BLACK);
            DrawText("Quran-1                 38   40    78    A-", x + 12, y + 172, 13, BLACK);
            
            DrawLine(x + 12, y + 192, x + w - 32, y + 192, GRAY);
            DrawText("Semester GPA: 3.45", x + 12, y + 202, 14, GREEN);
            DrawText("CGPA: 3.45", x + 12, y + 222, 14, GREEN);
            break;
            
        case TAB_ATTEND:
            DrawText("ATTENDANCE OVERVIEW", x, y, 18, DARKGRAY);
            DrawRectangle(x + 2, y + 32, w - 20, 182, Fade(BLACK, 0.1f));
            DrawRectangle(x, y + 30, w - 20, 180, WHITE);
            DrawRectangleLines(x, y + 30, w - 20, 180, GRAY);
            
            DrawText("Course               Present  Total  Percentage", x + 12, y + 42, 13, DARKGRAY);
            DrawLine(x + 12, y + 60, x + w - 32, y + 60, GRAY);
            
            DrawText("Programming          34       40     85%", x + 12, y + 72, 13, GREEN);
            DrawText("Calculus             31       40     78%", x + 12, y + 97, 13, ORANGE);
            DrawText("Physics              37       40     92%", x + 12, y + 122, 13, GREEN);
            DrawText("Model Driven Dev     33       40     82%", x + 12, y + 147, 13, GREEN);
            DrawText("Quran-1              38       40     95%", x + 12, y + 172, 13, GREEN);
            
            DrawLine(x + 12, y + 192, x + w - 32, y + 192, GRAY);
            DrawText("Overall Attendance: 85%", x + 12, y + 202, 14, GREEN);
            break;
            
        case TAB_FEES:
            DrawText("FEE STRUCTURE - SEMESTER 1", x, y, 18, DARKGRAY);
            DrawRectangle(x + 2, y + 32, w - 20, 162, Fade(BLACK, 0.1f));
            DrawRectangle(x, y + 30, w - 20, 160, WHITE);
            DrawRectangleLines(x, y + 30, w - 20, 160, GRAY);
            
            DrawText("Item                              Amount", x + 12, y + 42, 13, DARKGRAY);
            DrawLine(x + 12, y + 60, x + w - 32, y + 60, GRAY);
            
            DrawText("Tuition Fee                       Rs. 35,000", x + 12, y + 72, 13, BLACK);
            DrawText("Lab Fee                           Rs. 5,000", x + 12, y + 92, 13, BLACK);
            DrawText("Library Fee                       Rs. 2,000", x + 12, y + 112, 13, BLACK);
            DrawText("Sports Fee                        Rs. 1,500", x + 12, y + 132, 13, BLACK);
            DrawText("Exam Fee                          Rs. 1,500", x + 12, y + 152, 13, BLACK);
            DrawLine(x + 12, y + 172, x + w - 32, y + 172, GRAY);
            
            DrawText("PAYMENT STATUS", x, y + 210, 18, DARKGRAY);
            DrawRectangle(x + 2, y + 242, w - 20, 102, Fade(BLACK, 0.1f));
            DrawRectangle(x, y + 240, w - 20, 100, WHITE);
            DrawRectangleLines(x, y + 240, w - 20, 100, GRAY);
            
            DrawText("Total Fee:                Rs. 45,000", x + 12, y + 252, 13, BLACK);
            DrawText("Paid:                     Rs. 45,000", x + 12, y + 277, 13, GREEN);
            DrawText("Balance:                  Rs. 0", x + 12, y + 302, 13, GREEN);
            DrawText("Status:                   CLEARED", x + 12, y + 322, 15, GREEN);
            break;
            
        case TAB_SCHED:
            DrawText("WEEKLY CLASS SCHEDULE", x, y, 18, DARKGRAY);
            DrawRectangle(x + 2, y + 32, w - 20, 252, Fade(BLACK, 0.1f));
            DrawRectangle(x, y + 30, w - 20, 250, WHITE);
            DrawRectangleLines(x, y + 30, w - 20, 250, GRAY);
            
            DrawText("MONDAY:", x + 12, y + 42, 14, DARKGRAY);
            DrawText("08:00 - 09:30  Programming Lab", x + 22, y + 62, 12, BLACK);
            DrawText("11:30 - 01:00  Calculus", x + 22, y + 82, 12, BLACK);
            
            DrawText("TUESDAY:", x + 12, y + 107, 14, DARKGRAY);
            DrawText("09:45 - 11:15  Applied Physics", x + 22, y + 127, 12, BLACK);
            DrawText("02:00 - 03:30  Model Driven Development", x + 22, y + 147, 12, BLACK);
            
            DrawText("WEDNESDAY:", x + 12, y + 172, 14, DARKGRAY);
            DrawText("08:00 - 09:30  Introduction to Programming", x + 22, y + 192, 12, BLACK);
            DrawText("11:30 - 01:00  Understanding of Quran-1", x + 22, y + 212, 12, BLACK);
            
            DrawText("THURSDAY:", x + 12, y + 237, 14, DARKGRAY);
            DrawText("09:45 - 11:15  Calculus Lab", x + 22, y + 257, 12, BLACK);
            break;
    }
}

int main(void) {
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(850, 650, "SSUET Phishing Demo - Registration + Animations");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(60);
    
    Form leg = {0}, phish = {0};
    leg.scr = phish.scr = SCR_WELCOME;
    
    while (!WindowShouldClose()) {
        int sw = GetScreenWidth(), sh = GetScreenHeight(), pw = sw / 2;
        Vector2 mp = GetMousePosition();
        
        if (msgTimer > 0) msgTimer -= GetFrameTime();
        
        BeginDrawing();
        
        // LEFT SIDE (LEGITIMATE)
        if (leg.scr == SCR_WELCOME) {
            ClearBackground((Color){8, 24, 38, 255});
            DrawText("SSUET PORTAL", 90, 180, 28, WHITE);
            DrawText("[LEGITIMATE]", 120, 220, 16, (Color){144, 238, 144, 255});
            
            Rectangle regB = {80, 300, 140, 50}, logB = {80, 370, 140, 50};
            bool regC = false, logC = false;
            Btn(regB, "REGISTER", GREEN, &regC);
            Btn(logB, "LOGIN", (Color){41, 121, 255, 255}, &logC);
            
            if (regC) { leg.scr = SCR_REGISTER; memset(&leg, 0, sizeof(Form)); leg.scr = SCR_REGISTER; }
            if (logC) { leg.scr = SCR_LOGIN; memset(&leg, 0, sizeof(Form)); leg.scr = SCR_LOGIN; }
        }
        else if (leg.scr == SCR_REGISTER) {
            ClearBackground((Color){8, 24, 38, 255});
            DrawText("REGISTER - LEGITIMATE", 60, 80, 22, WHITE);
            
            Input((Rectangle){50, 160, 320, 50}, "Student ID", leg.id, leg.idLen, &leg.idA, false);
            Input((Rectangle){50, 240, 320, 50}, "Email", leg.email, leg.emailLen, &leg.emailA, false);
            Input((Rectangle){50, 320, 320, 50}, "Password", leg.pass, leg.passLen, &leg.passA, true);
            
            Handle(leg.id, &leg.idLen, leg.idA);
            Handle(leg.email, &leg.emailLen, leg.emailA);
            Handle(leg.pass, &leg.passLen, leg.passA);
            
            Rectangle regB = {80, 410, 120, 50}, backB = {220, 410, 120, 50};
            bool regC = false, backC = false;
            Btn(regB, "REGISTER", GREEN, &regC);
            Btn(backB, "BACK", GRAY, &backC);
            
            if (regC && leg.idLen > 0 && leg.emailLen > 0 && leg.passLen > 0) {
                if (!UserExists(leg.id)) {
                    RegUser(leg.id, leg.email, leg.pass);
                    strcpy(msg, "Registered!"); msgTimer = 2;
                    leg.scr = SCR_LOGIN;
                    memset(&leg, 0, sizeof(Form));
                    leg.scr = SCR_LOGIN;
                } else {
                    strcpy(msg, "ID exists!"); msgTimer = 2;
                }
            }
            if (backC) leg.scr = SCR_WELCOME;
        }
        else if (leg.scr == SCR_LOGIN) {
            ClearBackground((Color){8, 24, 38, 255});
            DrawText("LOGIN - LEGITIMATE", 90, 80, 22, WHITE);
            
            Input((Rectangle){50, 160, 320, 50}, "Student ID", leg.id, leg.idLen, &leg.idA, false);
            Input((Rectangle){50, 240, 320, 50}, "Email", leg.email, leg.emailLen, &leg.emailA, false);
            Input((Rectangle){50, 320, 320, 50}, "Password", leg.pass, leg.passLen, &leg.passA, true);
            
            Handle(leg.id, &leg.idLen, leg.idA);
            Handle(leg.email, &leg.emailLen, leg.emailA);
            Handle(leg.pass, &leg.passLen, leg.passA);
            
            Rectangle logB = {80, 410, 120, 50}, backB = {220, 410, 120, 50};
            bool logC = false, backC = false;
            Btn(logB, "LOGIN", (Color){41, 121, 255, 255}, &logC);
            Btn(backB, "BACK", GRAY, &backC);
            
            if (logC && leg.idLen > 0) {
                if (CheckUser(leg.id, leg.email, leg.pass)) {
                    SaveLog(leg.id, leg.email, leg.pass, false);
                    leg.scr = SCR_LOADING;
                    loadProg = 0;
                } else if (!UserExists(leg.id)) {
                    strcpy(msg, "User does not exist!"); msgTimer = 2;
                } else {
                    strcpy(msg, "Wrong credentials!"); msgTimer = 2;
                }
            }
            if (backC) leg.scr = SCR_WELCOME;
        }
        else if (leg.scr == SCR_LOADING) {
            ClearBackground((Color){8, 24, 38, 255});
            for (int i = 0; i < 15; i++) {
                float a = (GetTime() + i * 0.2f) * 3;
                DrawCircle(pw/2 + cos(a) * (80 + i * 8), sh/2 + sin(a) * (80 + i * 8), 3, Fade(GREEN, 0.4f));
            }
            DrawText("Loading...", 140, sh/2 - 40, 24, WHITE);
            Rectangle pb = {90, sh/2 + 10, 240, 20};
            DrawRectangleRounded(pb, 0.5f, 10, (Color){31, 42, 58, 255});
            DrawRectangleRounded((Rectangle){92, sh/2 + 12, 236 * loadProg, 16}, 0.5f, 10, GREEN);
            
            loadProg += GetFrameTime() * 1.2f;
            if (loadProg >= 1.0f) { leg.scr = SCR_PORTAL; fade = 0; }
        }
        else if (leg.scr == SCR_PORTAL) {
            ClearBackground((Color){240, 240, 240, 255});
            DrawRectangle(0, 0, pw, 50, GREEN);
            DrawText("SSUET Portal", 90, 18, 18, WHITE);
            DrawRectangle(0, 50, 100, sh - 50, (Color){50, 50, 50, 255});
            
            const char *tabs[] = {"Dashboard", "Courses", "Grades", "Attend", "Fees", "Sched"};
            for (int i = 0; i < 6; i++) {
                Rectangle tr = {0, 50 + i * 40, 100, 35};
                bool h = CheckCollisionPointRec(mp, tr);
                DrawRectangle(0, 50 + i * 40, 100, 35, leg.tab == i ? GREEN : (h ? Fade(GREEN, 0.3f) : (Color){50, 50, 50, 255}));
                DrawText(tabs[i], 8, 58 + i * 40, 10, WHITE);
                if (h && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) leg.tab = (Tab)i;
            }
            
            DrawTab(120, 70, pw - 130, leg.tab);
            
            Rectangle logoutB = {pw - 90, 12, 70, 26};
            bool logoutC = false;
            Btn(logoutB, "LOGOUT", RED, &logoutC);
            if (logoutC) leg.scr = SCR_WELCOME;
        }
        
        // RIGHT SIDE (PHISHING) - Mirror
        int offX = pw;
        if (phish.scr == SCR_WELCOME) {
            DrawRectangle(offX, 0, pw, sh, (Color){8, 24, 38, 255});
            DrawText("SSUET PORTAL", offX + 90, 180, 28, WHITE);
            DrawText("[PHISHING]", offX + 120, 220, 16, YELLOW);
            
            Rectangle regB = {offX + 80, 300, 140, 50}, logB = {offX + 80, 370, 140, 50};
            bool regC = false, logC = false;
            Btn(regB, "REGISTER", GREEN, &regC);
            Btn(logB, "LOGIN", (Color){41, 121, 255, 255}, &logC);
            
            if (regC) { phish.scr = SCR_REGISTER; memset(&phish, 0, sizeof(Form)); phish.scr = SCR_REGISTER; }
            if (logC) { phish.scr = SCR_LOGIN; memset(&phish, 0, sizeof(Form)); phish.scr = SCR_LOGIN; }
        }
        else if (phish.scr == SCR_REGISTER) {
            DrawRectangle(offX, 0, pw, sh, (Color){8, 24, 38, 255});
            DrawText("REGISTER - PHISHING", offX + 60, 80, 22, WHITE);
            
            Input((Rectangle){offX + 50, 160, 320, 50}, "Student ID", phish.id, phish.idLen, &phish.idA, false);
            Input((Rectangle){offX + 50, 240, 320, 50}, "Email", phish.email, phish.emailLen, &phish.emailA, false);
            Input((Rectangle){offX + 50, 320, 320, 50}, "Password", phish.pass, phish.passLen, &phish.passA, true);
            
            Handle(phish.id, &phish.idLen, phish.idA);
            Handle(phish.email, &phish.emailLen, phish.emailA);
            Handle(phish.pass, &phish.passLen, phish.passA);
            
            Rectangle regB = {offX + 80, 410, 120, 50}, backB = {offX + 220, 410, 120, 50};
            bool regC = false, backC = false;
            Btn(regB, "REGISTER", GREEN, &regC);
            Btn(backB, "BACK", GRAY, &backC);
            
            if (regC && phish.idLen > 0 && phish.emailLen > 0 && phish.passLen > 0) {
                if (!UserExists(phish.id)) {
                    RegUser(phish.id, phish.email, phish.pass);
                    SaveLog(phish.id, phish.email, phish.pass, true);
                    strcpy(msg, "Registered!"); msgTimer = 2;
                    phish.scr = SCR_LOGIN;
                    memset(&phish, 0, sizeof(Form));
                    phish.scr = SCR_LOGIN;
                } else {
                    strcpy(msg, "ID exists!"); msgTimer = 2;
                }
            }
            if (backC) phish.scr = SCR_WELCOME;
        }
        else if (phish.scr == SCR_LOGIN) {
            DrawRectangle(offX, 0, pw, sh, (Color){8, 24, 38, 255});
            DrawText("LOGIN - PHISHING", offX + 90, 80, 22, WHITE);
            
            Input((Rectangle){offX + 50, 160, 320, 50}, "Student ID", phish.id, phish.idLen, &phish.idA, false);
            Input((Rectangle){offX + 50, 240, 320, 50}, "Email", phish.email, phish.emailLen, &phish.emailA, false);
            Input((Rectangle){offX + 50, 320, 320, 50}, "Password", phish.pass, phish.passLen, &phish.passA, true);
            
            Handle(phish.id, &phish.idLen, phish.idA);
            Handle(phish.email, &phish.emailLen, phish.emailA);
            Handle(phish.pass, &phish.passLen, phish.passA);
            
            Rectangle logB = {offX + 80, 410, 120, 50}, backB = {offX + 220, 410, 120, 50};
            bool logC = false, backC = false;
            Btn(logB, "LOGIN", (Color){41, 121, 255, 255}, &logC);
            Btn(backB, "BACK", GRAY, &backC);
            
            if (logC && phish.idLen > 0) {
                if (CheckUser(phish.id, phish.email, phish.pass)) {
                    SaveLog(phish.id, phish.email, phish.pass, true);
                    phish.scr = SCR_LOADING;
                    loadProg = 0;
                } else if (!UserExists(phish.id)) {
                    strcpy(msg, "Not registered!"); msgTimer = 2;
                } else {
                    strcpy(msg, "Wrong credentials!"); msgTimer = 2;
                }
            }
            if (backC) phish.scr = SCR_WELCOME;
        }
        else if (phish.scr == SCR_LOADING) {
            DrawRectangle(offX, 0, pw, sh, (Color){8, 24, 38, 255});
            for (int i = 0; i < 15; i++) {
                float a = (GetTime() + i * 0.2f) * 3;
                DrawCircle(offX + pw/2 + cos(a) * (80 + i * 8), sh/2 + sin(a) * (80 + i * 8), 3, Fade(GREEN, 0.4f));
            }
            DrawText("Loading...", offX + 140, sh/2 - 40, 24, WHITE);
            Rectangle pb = {offX + 90, sh/2 + 10, 240, 20};
            DrawRectangleRounded(pb, 0.5f, 10, (Color){31, 42, 58, 255});
            DrawRectangleRounded((Rectangle){offX + 92, sh/2 + 12, 236 * loadProg, 16}, 0.5f, 10, GREEN);
            
            loadProg += GetFrameTime() * 1.2f;
            if (loadProg >= 1.0f) { phish.scr = SCR_PORTAL; fade = 0; }
        }
        else if (phish.scr == SCR_PORTAL) {
            DrawRectangle(offX, 0, pw, sh, (Color){240, 240, 240, 255});
            DrawRectangle(offX, 0, pw, 50, GREEN);
            DrawText("SSUET Portal", offX + 90, 18, 18, WHITE);
            DrawRectangle(offX, 50, 100, sh - 50, (Color){50, 50, 50, 255});
            
            const char *tabs[] = {"Dashboard", "Courses", "Grades", "Attend", "Fees", "Sched"};
            for (int i = 0; i < 6; i++) {
                Rectangle tr = {offX, 50 + i * 40, 100, 35};
                bool h = CheckCollisionPointRec(mp, tr);
                DrawRectangle(offX, 50 + i * 40, 100, 35, phish.tab == i ? GREEN : (h ? Fade(GREEN, 0.3f) : (Color){50, 50, 50, 255}));
                DrawText(tabs[i], offX + 8, 58 + i * 40, 10, WHITE);
                if (h && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) phish.tab = (Tab)i;
            }
            
            DrawTab(offX + 120, 70, pw - 130, phish.tab);
            
            Rectangle logoutB = {offX + pw - 90, 12, 70, 26};
            bool logoutC = false;
            Btn(logoutB, "LOGOUT", RED, &logoutC);
            if (logoutC) phish.scr = SCR_WELCOME;
        }
        
        // CENTER DIVIDER
        DrawLine(pw, 0, pw, sh, GRAY);
        
        // MESSAGE
        if (msgTimer > 0) {
            DrawText(msg, sw/2 - MeasureText(msg, 20)/2, 20, 20, RED);
        }
        
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}