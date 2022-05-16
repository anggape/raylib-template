#define RAYGUI_IMPLEMENTATION
#include <raygui.h>
#include <raylib.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    InitWindow(720, 360, "sample");
    SetExitKey(0);

    int dropdownBox000Active = 0;
    bool dropDown000EditMode = false;

    int dropdownBox001Active = 0;
    bool dropDown001EditMode = false;

    int spinner001Value = 0;
    bool spinnerEditMode = false;

    int valueBox002Value = 0;
    bool valueBoxEditMode = false;

    char textBoxText[64] = "Text box";
    bool textBoxEditMode = false;

    int listViewScrollIndex = 0;
    int listViewActive = -1;

    int listViewExScrollIndex = 0;
    int listViewExActive = 2;
    int listViewExFocus = -1;
    const char *listViewExList[8] = {"This", "is",      "a",        "list view",
                                     "with", "disable", "elements", "amazing!"};

    char multiTextBoxText[256] = "Multi text box";
    bool multiTextBoxEditMode = false;
    Color colorPickerValue = RED;

    int sliderValue = 50;
    int sliderBarValue = 60;
    float progressValue = 0.4f;

    bool forceSquaredChecked = false;

    float alphaValue = 0.5f;

    int comboBoxActive = 1;

    int toggleGroupActive = 0;

    Vector2 viewScroll = {0, 0};

    bool exitWindow = false;
    bool showMessageBox = false;

    char textInput[256] = {0};
    bool showTextInputBox = false;

    char textInputFileName[256] = {0};

    SetTargetFPS(60);

    while (!exitWindow) {
        exitWindow = WindowShouldClose();

        if (IsKeyPressed(KEY_ESCAPE))
            showMessageBox = !showMessageBox;

        if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_S))
            showTextInputBox = true;

        if (IsFileDropped()) {
            int dropFileCount = 0;
            char **droppedFiles = GetDroppedFiles(&dropFileCount);

            if ((dropFileCount > 0) && IsFileExtension(droppedFiles[0], ".rgs"))
                GuiLoadStyle(droppedFiles[0]);

            ClearDroppedFiles();
        }

        BeginDrawing();

        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

        if (dropDown000EditMode || dropDown001EditMode)
            GuiLock();
        else if (!dropDown000EditMode && !dropDown001EditMode)
            GuiUnlock();

        forceSquaredChecked = GuiCheckBox((Rectangle){25, 108, 15, 15},
                                          "FORCE CHECK!", forceSquaredChecked);

        GuiSetStyle(TEXTBOX, TEXT_ALIGNMENT, GUI_TEXT_ALIGN_CENTER);
        if (GuiSpinner((Rectangle){25, 135, 125, 30}, NULL, &spinner001Value, 0,
                       100, spinnerEditMode))
            spinnerEditMode = !spinnerEditMode;
        if (GuiValueBox((Rectangle){25, 175, 125, 30}, NULL, &valueBox002Value,
                        0, 100, valueBoxEditMode))
            valueBoxEditMode = !valueBoxEditMode;
        GuiSetStyle(TEXTBOX, TEXT_ALIGNMENT, GUI_TEXT_ALIGN_LEFT);
        if (GuiTextBox((Rectangle){25, 215, 125, 30}, textBoxText, 64,
                       textBoxEditMode))
            textBoxEditMode = !textBoxEditMode;

        GuiSetStyle(BUTTON, TEXT_ALIGNMENT, GUI_TEXT_ALIGN_CENTER);

        if (GuiButton((Rectangle){25, 255, 125, 30},
                      GuiIconText(RAYGUI_ICON_FILE_SAVE, "Save File")))
            showTextInputBox = true;

        GuiGroupBox((Rectangle){25, 310, 125, 150}, "STATES");
        // GuiLock();
        GuiSetState(GUI_STATE_NORMAL);
        if (GuiButton((Rectangle){30, 320, 115, 30}, "NORMAL")) {
        }
        GuiSetState(GUI_STATE_FOCUSED);
        if (GuiButton((Rectangle){30, 355, 115, 30}, "FOCUSED")) {
        }
        GuiSetState(GUI_STATE_PRESSED);
        if (GuiButton((Rectangle){30, 390, 115, 30}, "#15#PRESSED")) {
        }
        GuiSetState(GUI_STATE_DISABLED);
        if (GuiButton((Rectangle){30, 425, 115, 30}, "DISABLED")) {
        }
        GuiSetState(GUI_STATE_NORMAL);

        comboBoxActive = GuiComboBox((Rectangle){25, 470, 125, 30},
                                     "ONE;TWO;THREE;FOUR", comboBoxActive);

        GuiSetStyle(DROPDOWNBOX, TEXT_ALIGNMENT, GUI_TEXT_ALIGN_LEFT);
        if (GuiDropdownBox((Rectangle){25, 65, 125, 30},
                           "#01#ONE;#02#TWO;#03#THREE;#04#FOUR",
                           &dropdownBox001Active, dropDown001EditMode))
            dropDown001EditMode = !dropDown001EditMode;

        GuiSetStyle(DROPDOWNBOX, TEXT_ALIGNMENT, GUI_TEXT_ALIGN_CENTER);
        if (GuiDropdownBox((Rectangle){25, 25, 125, 30}, "ONE;TWO;THREE",
                           &dropdownBox000Active, dropDown000EditMode))
            dropDown000EditMode = !dropDown000EditMode;

        listViewActive = GuiListView(
            (Rectangle){165, 25, 140, 140},
            "Charmander;Bulbasaur;#18#Squirtel;Pikachu;Eevee;Pidgey",
            &listViewScrollIndex, listViewActive);
        listViewExActive = GuiListViewEx(
            (Rectangle){165, 180, 140, 200}, listViewExList, 8,
            &listViewExFocus, &listViewExScrollIndex, listViewExActive);

        toggleGroupActive =
            GuiToggleGroup((Rectangle){165, 400, 140, 25},
                           "#1#ONE\n#3#TWO\n#8#THREE\n#23#", toggleGroupActive);

        if (GuiTextBoxMulti((Rectangle){320, 25, 225, 140}, multiTextBoxText,
                            256, multiTextBoxEditMode))
            multiTextBoxEditMode = !multiTextBoxEditMode;
        colorPickerValue = GuiColorPicker((Rectangle){320, 185, 196, 192}, NULL,
                                          colorPickerValue);

        sliderValue = GuiSlider((Rectangle){355, 400, 165, 20}, "TEST",
                                TextFormat("%2.2f", (float)sliderValue),
                                sliderValue, -50, 100);
        sliderBarValue = GuiSliderBar((Rectangle){320, 430, 200, 20}, NULL,
                                      TextFormat("%i", (int)sliderBarValue),
                                      sliderBarValue, 0, 100);
        progressValue = GuiProgressBar((Rectangle){320, 460, 200, 20}, NULL,
                                       NULL, progressValue, 0, 1);

        Rectangle view =
            GuiScrollPanel((Rectangle){560, 25, 100, 160}, NULL,
                           (Rectangle){560, 25, 200, 400}, &viewScroll);

        GuiPanel((Rectangle){560, 25 + 180, 100, 160}, "Panel Info");

        GuiGrid((Rectangle){560, 25 + 180 + 180, 100, 120}, NULL, 20, 2);

        GuiStatusBar(
            (Rectangle){0, GetScreenHeight() - 20, GetScreenWidth(), 20},
            "This is a status bar");

        alphaValue =
            GuiColorBarAlpha((Rectangle){320, 490, 200, 30}, NULL, alphaValue);

        if (showMessageBox) {
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(),
                          Fade(RAYWHITE, 0.8f));
            int result =
                GuiMessageBox((Rectangle){GetScreenWidth() / 2 - 125,
                                          GetScreenHeight() / 2 - 50, 250, 100},
                              GuiIconText(RAYGUI_ICON_EXIT, "Close Window"),
                              "Do you really want to exit?", "Yes;No");

            if ((result == 0) || (result == 2))
                showMessageBox = false;
            else if (result == 1)
                exitWindow = true;
        }

        if (showTextInputBox) {
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(),
                          Fade(RAYWHITE, 0.8f));
            int result = GuiTextInputBox(
                (Rectangle){GetScreenWidth() / 2 - 120,
                            GetScreenHeight() / 2 - 60, 240, 140},
                "Save", GuiIconText(RAYGUI_ICON_FILE_SAVE, "Save file as..."),
                "Introduce a save file name", "Ok;Cancel", textInput, NULL);

            if (result == 1) {
                strcpy(textInputFileName, textInput);
            }

            if ((result == 0) || (result == 1) || (result == 2)) {
                showTextInputBox = false;
                strcpy(textInput, "\0");
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return EXIT_SUCCESS;
}
