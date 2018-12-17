#include "gui.h"
#include "engine.h"
#include "camera.h"
GUI::GUI()
{

}

GUI::~GUI()
{
  ImGui::DestroyContext();
}

int GUI::Initialize(SDL_Window* window, SDL_GLContext context)
{
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO(); (void)io;

 	ImGui_ImplSDL2_InitForOpenGL(window, context);
 	ImGui_ImplOpenGL3_Init("#version 330");

  SDL_GetWindowSize(window, &m_width, &m_height);
  cout << "(" << m_width << "," << m_height << ")" << endl;

  //TODO: change font
  m_fontSmall = io.Fonts->AddFontFromFileTTF("../assets/RioGrande.ttf", 25);
  m_fontMed = io.Fonts->AddFontFromFileTTF("../assets/RioGrande.ttf", 50);
  m_fontBig = io.Fonts->AddFontFromFileTTF("../assets/RioGrande.ttf", 100);

 	return true;
}

bool GUI::Update(SDL_Window* window, Graphics* graphics)
{
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplSDL2_NewFrame(window);
  ImGui::NewFrame();

  ImGui::SetNextWindowPos(ImVec2(0,0), ImGuiCond_Always);
  ImGui::SetNextWindowSize(ImVec2 (m_width, m_height), ImGuiCond_Always);
  ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0,0,0,0));
  ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

  bool running = true;

  if (m_gameOver)
  {
    //bigger text first
    ImGui::PushFont(m_fontBig);

    ImGui::SetNextWindowPos(ImVec2(0,0));
    ImGui::SetNextWindowSize(ImVec2 (m_width, m_height));

    string gameOverDisplay = "Game Over!";
    ImVec2 gameOverSize = ImGui::CalcTextSize(gameOverDisplay.c_str());
    ImVec2 gameOverCursor = CalculateCenteredPos(gameOverSize);

    if (ImGui::Begin("GameOver", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar |ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoInputs))
    {
      ImGui::SetCursorPos(ImVec2(gameOverCursor.x, gameOverCursor.y - 240));
      ImGui::Text(gameOverDisplay.c_str());
    }
    ImGui::End();

    ImGui::PopFont();

    //then medium text
    ImGui::PushFont(m_fontMed);

    ImGui::SetNextWindowPos(ImVec2(0,0));
    ImGui::SetNextWindowSize(ImVec2 (m_width, m_height));

    string finalScoreDisplay = "Final Score: " + to_string(graphics->m_world->GetScore());
    ImVec2 finalScoreSize = ImGui::CalcTextSize(finalScoreDisplay.c_str());
    ImVec2 finalScoreCursor = CalculateCenteredPos(finalScoreSize);

    if (ImGui::Begin("FinalScore", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoInputs))
    {
      ImGui::SetCursorPos(ImVec2(finalScoreCursor.x, finalScoreCursor.y - 170));
      ImGui::Text(finalScoreDisplay.c_str());
    }
    ImGui::End();

    ImGui::PopFont();

    //finally small text
    ImGui::PushFont(m_fontSmall);

    ImGui::SetNextWindowPos(ImVec2(0,0));
    ImGui::SetNextWindowSize(ImVec2 (m_width, m_height));

    //High score notifier
    if (graphics->m_world->IsNewHighScore())
    {
      string congratsDisplay = "Congrats! You got a new high score!";
      ImVec2 congratsSize = ImGui::CalcTextSize(congratsDisplay.c_str());
      ImVec2 congratsCursor = CalculateCenteredPos(congratsSize);

      if (ImGui::Begin("CongratsMessage", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoInputs))
      {
        ImGui::SetCursorPos(ImVec2(congratsCursor.x, congratsCursor.y - 130));
        ImGui::Text(congratsDisplay.c_str());
      }
      ImGui::End();
    }

    //leaderboards
    string *topTenScores = graphics->m_world->GetTopTenStats();
    int initialYOffset = -100;
    for (int i = 0; i < 10; i++)
    {
      ImGui::SetNextWindowPos(ImVec2(0,0));
      ImGui::SetNextWindowSize(ImVec2 (m_width, m_height));

      string topPlayerDisplay = topTenScores[i];
      ImVec2 topPlayerSize = ImGui::CalcTextSize(topPlayerDisplay.c_str());
      ImVec2 topPlayerCursor = CalculateCenteredPos(topPlayerSize);

      string header = "Leaderboard" + to_string(i);

      if (ImGui::Begin(header.c_str(), NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoInputs))
      {
        ImGui::SetCursorPos(ImVec2(topPlayerCursor.x, topPlayerCursor.y + (initialYOffset + 40 * i)));
        ImGui::Text(topPlayerDisplay.c_str());
      }
      ImGui::End();
    }

    ImGui::SetNextWindowPos(ImVec2(0,0));
    ImGui::SetNextWindowSize(ImVec2 (m_width, m_height));

    string restartDisplay = "Restart";
    ImVec2 restartSize = ImGui::CalcTextSize(restartDisplay.c_str());
    ImVec2 restartCursor = CalculateCenteredPos(restartSize);
    
    string exitDisplay = "Exit";
    ImVec2 exitSize = ImGui::CalcTextSize(exitDisplay.c_str());
    ImVec2 exitCursor = CalculateCenteredPos(exitSize);

    if (ImGui::Begin("UserOptions", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar))
    {
      ImGui::SetCursorPos(ImVec2(restartCursor.x, restartCursor.y + 295));
      if (ImGui::Button(restartDisplay.c_str()))
      {
        cout << "restarting" << endl;
        graphics->m_world->Reset();
      }

      ImGui::SetCursorPos(ImVec2(exitCursor.x, exitCursor.y + 335));
      if (ImGui::Button(exitDisplay.c_str()))
      {
        cout << "exiting" << endl;
        running = false;
      }
    }
    ImGui::End();

    ImGui::PopFont();
  }
  else
  {
    ImGui::PushFont(m_fontSmall);

    if (ImGui::Begin("HUD", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoInputs))
    {
      ImGui::PushFont(m_fontMed);

      int minutes = m_timeLeft / 60;
      string minutesDisplay;
      if (minutes > 0)
      {
        minutesDisplay = to_string(minutes) + " ";
      }
      else
      {
        minutesDisplay = "";
      }
      int seconds = m_timeLeft % 60;
      string secondsDisplay;
      if (seconds < 10)
      {
        secondsDisplay = "0" + to_string(seconds);
      }
      else
      {
        secondsDisplay = to_string(seconds);
      }
      string timerDisplay = minutesDisplay + secondsDisplay;
      ImVec2 timerSize = ImGui::CalcTextSize(timerDisplay.c_str());
      ImVec2 timerCursor = CalculateCenteredPos(timerSize);
      ImGui::SetCursorPos(ImVec2(timerCursor.x,timerCursor.y - (m_height/2) + 30));
      //cout << timerDisplay << endl;
      ImGui::Text(timerDisplay.c_str());

      ImGui::PopFont();

      string scoreDisplay = "Score: " + to_string(graphics->m_world->GetScore());
      ImGui::SetCursorPos(ImVec2(10,0));
      ImGui::Text(scoreDisplay.c_str());
      
      //Add Ammo Count
      string ammoDisplay = "Ammo: " + to_string(graphics->m_world->GetAmmoCount());
      ImGui::SetCursorPos(ImVec2(10,30));
      ImGui::Text(ammoDisplay.c_str());
    }
    ImGui::End();

    ImGui::PopFont();
    
  }
  
  ImGui::PopStyleColor(1);
  ImGui::PopStyleVar(1);

  return running;
}

void GUI::Render()
{
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

ImVec2 GUI::CalculateCenteredPos(ImVec2 textSize)
{
  ImVec2 centerOfWindow = ImVec2(m_width/2, m_height/2);
  //cout << "CENTER OF WINDOW" << endl;
  //cout << "(" << centerOfWindow.x << "," << centerOfWindow.y << ")" << endl;

  ImVec2 textSizeOffset = ImVec2(textSize.x/2, textSize.y/2);
  //cout << "TEXT OFFSET" << endl;
  //cout << "(" << textSizeOffset.x << "," << textSizeOffset.y << ")" << endl;

  ImVec2 centeredCursorPos = ImVec2(
    centerOfWindow.x - textSizeOffset.x,
    centerOfWindow.y - textSizeOffset.y);
  //cout << "CENTERED CURSOR" << endl;
  //cout << "(" << centeredCursorPos.x << "," << centeredCursorPos.y << ")" << endl;

  return centeredCursorPos;
}

void GUI::SetGameOver(bool gameOver)
{
  m_gameOver = gameOver;
}

void GUI::SetTimeLeft(int timeLeft)
{
  m_timeLeft = timeLeft;
}