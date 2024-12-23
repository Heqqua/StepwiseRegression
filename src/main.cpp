#include <wx/wx.h>
#include <wx/tokenzr.h>
#include <wx/log.h>
#include "regression.h"
#include <iostream>


class MyApp : public wxApp {
public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame {
public:
    MyFrame(const wxString& title);

private:
    wxTextCtrl* inputX;
    wxTextCtrl* inputY;
    wxTextCtrl* output;

    void OnCalculate(wxCommandEvent& event);
};

void MyFrame::OnCalculate(wxCommandEvent& event)
{
    wxLogDebug(L"Начало вычислений.");
    // std::cout << "Начало вычислений.\n";

    try {
        wxString inputXStr = inputX->GetValue();
        wxString inputYStr = inputY->GetValue();
        // wxLogDebug("Получены данные: X = %s, Y = %s", inputXStr, inputYStr);

        // Разделение строк на числа
        std::vector<double> x, y;
        wxStringTokenizer tokenizerX(inputXStr, ",");
        while (tokenizerX.HasMoreTokens()) {
            wxString token = tokenizerX.GetNextToken();
            // wxLogDebug("Обрабатываем X-значение: %s", token);
            x.push_back(wxAtof(token));
        }

        wxStringTokenizer tokenizerY(inputYStr, ",");
        while (tokenizerY.HasMoreTokens()) {
            wxString token = tokenizerY.GetNextToken();
            // wxLogDebug("Обрабатываем Y-значение: %s", token);
            y.push_back(wxAtof(token));
        }

        // Проверка длины массивов
        if (x.size() != y.size()) {
            throw std::runtime_error("Количество элементов X и Y должно совпадать.");
        }

        // wxLogDebug("Размеры массивов совпадают: X = %d, Y = %d", x.size(), y.size());

        // Выполнение регрессии
        int M = 2; // Степень полинома
        std::vector<double> coefficients = performRegression(x, y, M);

        // wxLogDebug("Регрессия выполнена, коэффициенты получены.");

        std::cout << coefficients.size() << std::endl;

        // Формирование результата
        wxString result;
        result = wxString(L"Результаты регрессии:\n", wxConvLibc);
        std::cout << result.ToAscii() << std::endl;
        for (size_t i = 0; i < coefficients.size(); ++i) {
            std::cout << coefficients[i] << std::endl;
            result += wxString::Format(L"Коэффициент при x^%d: %.5lf\n", static_cast<int>(i), coefficients[i]);
            // result = wxString::Format(L"Коэффициент при %d  %f\n", 1, 1.2);
            // wxLogDebug("Коэффициент %d: %.5lf", static_cast<int>(i), coefficients[i]);
        }

        std::cout << result << std::endl;

        output->SetValue(result);
    }
    catch (const std::exception& e) {
        // wxMessageBox(wxString::Format("Ошибка: %s", e.what()), "Ошибка", wxOK | wxICON_ERROR);
        // wxLogError("Ошибка: %s", e.what());
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

}



bool MyApp::OnInit() {
    wxLog::SetActiveTarget(new wxLogStderr); // Включаем вывод отладочных сообщений в консоль
    MyFrame* frame = new MyFrame("Степенная регрессия");
    frame->Show(true);

    return true;
}

MyFrame::MyFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title) {
    
    wxPanel* panel = new wxPanel(this, -1);
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    inputX = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(400, 30));
    inputY = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(400, 30));
    output = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(400, 100), wxTE_MULTILINE | wxTE_READONLY);

    wxButton* button = new wxButton(panel, wxID_ANY, "Рассчитать", wxDefaultPosition, wxDefaultSize);
    button->Bind(wxEVT_BUTTON, &MyFrame::OnCalculate, this);

    sizer->Add(inputX, 0, wxALL | wxEXPAND, 5);
    sizer->Add(inputY, 0, wxALL | wxEXPAND, 5);
    sizer->Add(button, 0, wxALL | wxCENTER, 5);
    sizer->Add(output, 1, wxALL | wxEXPAND, 5);

    panel->SetSizer(sizer);
}

wxIMPLEMENT_APP(MyApp);
