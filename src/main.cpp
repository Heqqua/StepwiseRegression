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
    wxMessageBox("Calculate button pressed");
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
    sizer->Add(output, 1, wxALL | wxEXPAND);
    }
wxIMPLEMENT_APP(MyApp);