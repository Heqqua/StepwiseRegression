#include <wx/wx.h>
#include "regression.h"

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
    try {
        // Получение текста из полей ввода
        wxString inputXStr = inputX->GetValue();
        wxString inputYStr = inputY->GetValue();

        // Разделение строк на числа
        std::vector<double> x, y;
        wxArrayString xArray = wxStringTokenize(inputXStr, ",");
        wxArrayString yArray = wxStringTokenize(inputYStr, ",");

        for (const auto& val : xArray) {
            x.push_back(wxAtof(val));
        }
        for (const auto& val : yArray) {
            y.push_back(wxAtof(val));
        }

        // Проверка длины массивов
        if (x.size() != y.size()) {
            throw std::runtime_error("Количество элементов X и Y должно совпадать.");
        }

        // Выполнение регрессии
        int M = 2; // Степень полинома, можно сделать параметром
        std::vector<double> coefficients = performRegression(x, y, M);

        // Формирование результата
        wxString result = "Результаты регрессии:\n";
        for (size_t i = 0; i < coefficients.size(); ++i) {
            result += wxString::Format("Коэффициент при x^%d: %.5f\n", i, coefficients[i]);
        }

        // Отображение результата
        output->SetValue(result);
    }
    catch (const std::exception& e) {
        wxMessageBox(wxString::Format("Ошибка: %s", e.what()), "Ошибка", wxOK | wxICON_ERROR);
    }
}


bool MyApp::OnInit() {
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

    panel->SetSizer(sizer);  // Добавлено для корректного отображения
}

wxIMPLEMENT_APP(MyApp);
