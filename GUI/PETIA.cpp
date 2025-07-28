//final petia code

#include<iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Clipboard.hpp>
#include <vector>
#include <ctime>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cctype>

using namespace std;
using namespace sf;

// ==============================================
// DATA STRUCTURES
// ==============================================

// System data structures

struct AdoptionRequest {
    string request_id, user_id, pet_id, status, date;
    int score;
};

struct User {
    string id;
    string name;
    string email;
    string password;
    string phone;
    string role;
    int requestcounter = 0;
    vector<string> adoptionRequestIds; // Stores request IDs instead of full objects
};

struct Admin {
    string admin_id;
    string name;
    string email;
    string password;
    string phone;
};

struct search {
    Text pet_name, pet_id, pet_breed, pet_species, pet_health, pet_availability, pet_age;
    Text requesting;
    Sprite box;
    Sprite filled_heart, empty_heart;
    Sprite below;
    Text name_value, id_value, species_value, health_value, age_value, breed_value;

}search_array[20], pets_array[20];


struct Pet {
    string id, name, breed, species, health, availability, age;
    string image_path;
    Texture photo_tex;
    Sprite photo;
    bool loadImage() {
        if (!photo_tex.loadFromFile(image_path))
            return false;
        photo.setTexture(photo_tex);
        float target_width = 200.0f;
        float target_height = 200.0f;
        float scale_x = target_width / photo_tex.getSize().x;
        float scale_y = target_height / photo_tex.getSize().y;
        photo.setScale(scale_x, scale_y);

        return true;
    }
};

struct cardadmin {
    Sprite spr_rectangle;
    Sprite acceptButton_spr, rejectButton_spr;
    Text cpet_ID, crequest_ID, cDate, cscore_req, cuser_ID;
    Text pet_ID, request_ID, Date, score_req, user_ID, approve, reject;
}admincard;

struct carduser {
    Sprite spr_rectangle;
    Text pet_ID, request_ID, Date, score_req, status;
    Text cpet_ID, crequest_ID, cDate, cscore_req, cstatus;
}usercard;

struct adminpage {
    Sprite decisionbutton, addbutton, removebutton, editbutton;
    Text decision, add, remove, edit;
}padmin;


struct favourite {
    string user_id;
    string path, name, id;
    Text name_text, id_text, name_value, id_value, req_text;
    Texture photo_tex;
    Sprite photo, box, remove, req_box, under;
    bool loadImage() {
        if (!photo_tex.loadFromFile(path))
            return false;
        photo.setTexture(photo_tex);
        float target_width = 200.0f;
        float target_height = 200.0f;
        float scale_x = target_width / photo_tex.getSize().x;
        float scale_y = target_height / photo_tex.getSize().y;
        photo.setScale(scale_x, scale_y);

        return true;
    }

};

struct thisnotification {
    bool decision;
    string user_id, pet_id;
    string notification;
    Text notification_text;
    Sprite below, x_not;
};


// ==============================================
// GLOBAL VARIABLES
// ==============================================


// Application state variables
RenderWindow window(VideoMode(1300, 900), "PETIA");
RectangleShape mouseRectangle(Vector2f(10, 30));
string selection;   //admin or user

// Data storage vectors
vector<User> users;
vector<Admin> admins;
vector<AdoptionRequest> adoptionRequests;
vector<favourite>fav;
vector<thisnotification> not_vector;
vector<Pet> search_out;
vector<Pet> pets = {
    {"petia_1","moro","golden","dogs","vaccinated","available","2*years","moro2.jpg"},
    {"petia_2","freska","lulu","dogs","unvaccinated","available","3*months","freska.jpg"},
    {"petia_3","bonita","persian","cats","injured","available","3*years","bonita1.png"},
    {"petia_4","luna","himalayan","cats","vaccinated","available","6*months","luna.jpg"},
    {"petia_5","bondok","german","dogs","vaccinated","available","3*months","bondok.jpg"},
    {"petia_6","angel","cockatoo","birds","healthy","available","2*years","angel.jpg"},
    {"petia_7","sultan","cockatoo","birds","injured","available","3*years","sultan.jpg"}

};

// File paths
const string USER_FILE = "userData.txt";
const string ADMIN_FILE = "adminData.txt";
const string PET_FILE = "petData.txt";
const string NOTIFICATION_FILE = "notificationData.txt";
const string REQUEST_FILE = "requestData.txt";
const string FAVOURITE_FILE = "fav.txt";

// ==============================================
// UI COMPONENTS - COMMON
// ==============================================

// Fonts
Font font;
Font font_search;

// ScrollOffsets
float scrollOffset = 0.0f;
float scrollOffset2 = 0;
float scrollOffset_notif = 0;

//Colors
void setTextColorWhite(Text text) {
    text.setFillColor(Color::White);
}

// ==============================================
// UI COMPONENTS - LOGIN/REGISTER PAGES
// ==============================================

Texture bell_after_tex;
Sprite bell_after;
Texture account_tex;
Sprite account;
Text user, admin, login, email, password, Register, userRegisteration;
Text name, id, phonenum, role, request, reject, accept;
Text pet_ID, request_ID, status, nrequest, signup;
Text Login, emailText, passwordText, confirm;
Text signup2, nameText, idText, emailRText, passwordRText, phonenumRText, roleRText;
Sprite spr_background1, userbutton, adminbutton;
Sprite spr_logInbackground, spr_registerationback;
Sprite emailValue, passwordValue, namevalue, idvalue, emailRvalue, passwordRvalue, phonenumvalue, rolevalue;
Sprite confirmbutton, signupbutton2, signupbutton, addButtonSprite;
Texture eye_closed_tex;
Sprite eye_closed;
string emailInput, passwordInput;
string nameInput, idInput, emailRInput, passwordRInput, phonenumRInput, roleRInput;

bool eye_bool = false;
bool isPasswordVisible = false;
bool appear = true;
bool isEmailSelected = false, isPasswordSelected = false;
bool isNameSelected = false, isIdSelected = false, isEmailRSelected = false;
bool isPasswordRSelected = false, isPhoneNumSelected = false, isRoleSelected = false;


// ==============================================
// UI COMPONENTS - AUTHENTICATION PAGE
// ==============================================

Texture eyetex, back_tex, background_authen_tex, danger_tex, authen_button_tex;
Sprite eye, back_sp, background_authen, danger, authen_button;
Text ok_athen, authen, authen_pass, enter_authen;


// ==============================================
// UI COMPONENTS - Requests
// ==============================================

Texture tex_backgroundReq, arrow_buttontex, tex_rectangle1, tex_rectangle2;
Texture button_tex, catpet_tex, dogpet_tex, backButtonTexture;
Texture bgTexture, boxTexture, uploadButtonTexture, addButtonTexture, buttontex;
Texture tex_background1, tex_logInbackground, write_button, tex_registerationback, rectangle;

Sprite spr_backgroundReq, arrow_buttonspr, arrow_buttonspr2, registerbutton;
Sprite catpet_spr, dogpet_spr, backButton;
Sprite background;

// ==============================================
// UI COMPONENTS - ADD PET PAGE
// ==============================================

Texture add_back_tex, add_button_tex, add_box_tex;
Sprite add_back, add_boxname, add_boxbreed, add_boxspecies, add_boxage, add_boxhealth, add_buton, add_pic_button;
Text p_name, p_breed, p_species, p_age, p_health, p_image, p_ok, p_addImage;
Text pet_name, pet_breed, pet_species, pet_age, pet_health;
Text pet_name_text, pet_age_text, pet_health_text, pet_breed_text, pet_species_text;
Text titleText, addButtonText, uploadButtonText;

// ==============================================
// UI COMPONENTS - EDIT PET PAGE
// ==============================================

Texture back_edit_tex, button_edit_tex, edit_box_tex;;
Sprite back_edit, name_e, age_e, health_e, breed_e, species_e;
Text name_ed, age_ed, health_ed, breed_ed, species_ed;
Sprite edit_box_id, edit_box;
Text name_edit, age_edit, health_edit, breed_edit, species_edit, id_edit;
Text edit_id, edit_name, edit_age, edit_health, edit_breed, edit_species;
bool name_selectEdit = false, age_selectEdit = false, health_selectEdit = false, breed_selectEdit = false, species_selectEdit = false;
bool id_boxEdit = false, other_box = false;
Text UpdateBoxText;
Sprite updateBOX;
string userid_adoption;


// ==============================================
// UI COMPONENTS - USER PAGES
// ==============================================

string input_search;
Texture textBackUser, tex_box, tex_bell, tex_envelope;
Sprite back_user, bell, envelope;
Text text_search;
Text not_found;
Texture tex_boxSearch;
Sprite box_search;
Texture tex_slide_s;
Sprite slide_sRight, slide_sLeft;
bool searching = false;
int cnt_notification = 0;

// ==============================================
// UI COMPONENTS - FAVORITES PAGE
// ==============================================

Texture filled_tex, empty_tex;
bool select_fav = false;
int index_fav;
Texture back_fav_tex, under_tex, remove_fav_tex;
Sprite back_fav;
float scroll_fav = 0;
Texture below_tex;
Texture FAV_tex, info_tex;
Sprite FAV, info;
Text title_fav;

// ==============================================
// UI COMPONENTS - ASSESSMENT/QUIZ
// ==============================================

Texture quizbackground_tex, ansbutton, assessFinishedback, closetex;
Sprite quizbackground_spr, ans11, ans12, ans21, ans22, ans31, ans32, ans41, ans42, sprfinish, okButton, startOkButton, startCloseButton;
Text q1, q2, q3, q4, q1a, q1b, q2a, q2b, q3a, q3b, q4a, q4b, okButtonText, startText, closeButtonText, thankYouText;
bool showfinishedpage = false;
bool showStartPage = true;
bool assessmentStarted = false;
Color defaultColor = Color::White;
int requestCounter = 1;
string selectedPetId = "";


// ==============================================
// Functions declration
// ==============================================

//files managment
void writeUsers(const vector<User>& users);
void readUsers(vector<User>& users);
void writeAdmins(const vector<Admin>& admins);
void readAdmins(vector<Admin>& admins);
void writePets(const vector<Pet>& pets);
void readPets(vector<Pet>& pets);
void writeAdoptionRequests(const vector<AdoptionRequest>& adoptionRequests);
void readAdoptionRequests(vector<AdoptionRequest>& adoptionRequests);
void writeNotification(const vector<thisnotification>& not_vector);
void readNotification(vector<thisnotification>& not_vector);
void writefavourites(const vector<favourite>& fav);
void readfavourites(vector<favourite>& fav);
void loadAllData();
void saveAllData();

// First page
void makePage_1();
void drawPage_1();
void firstpage();

// Log in/Registeration pages
void makelogInpage();
void drawlogInpage();
void loginpage();
void centerTextInBox(Text& text, const FloatRect& box);
void makeregister_adminPage();
void drawRegisteration_Admin();
void register_adminPage();
void makeregisterationPage();
void drawregisterationPage();
void registerationPage();

// Admin pages
void makeAdmindecision();
void drawAdmindecision(RenderWindow& window);
void Admindecisionpage();
void centerTextInBox1(Text& text, const Sprite& box);
void runRemoveScreen();
void makeadminpage();
void drawadminpage();
void adminpage();
void makeaddAdmin();
void drawAddAdmin();
void addadmin();
string addwindow();
void makeUpdate();
void drawUpdate();
void Updatepet();

// User pages
void search(string search_value, vector<Pet>& search_output);
void showNotificationsScreen();
void makeviewrequest();
void drawviewrequest(RenderWindow& window);
void viewrequestpage();
void make_user();
void drawUser();
void page_user();
void make_fav();
void draw_fav();
void fav_page();
void info_page();
//assesment pages
void makeStartPage();
void makequiz1();
void drawquiz1();
void makequiz2();
void drawquiz2();
void makefinishedpage();
int runAdoptionQuiz(const string& petId);
string getCurrentDate();
bool hasPendingRequest(const string& petId);

//checking validation
string checkvalid(string email, string password);
void errorbox(string text, int x, int y);
bool ckeck_email_regis(string email);
bool check_pass_regis(string pass);
bool check_gmail(string email);
void athentication_page();
void drawClippedText(sf::RenderWindow& window, const sf::Text& text, const sf::Sprite& box);
void added(string word, int x, int y);


int main() {

    loadAllData();

    firstpage();

    saveAllData();
    return 0;
}

// FILE HANDELING functions

void loadAllData() {
    readUsers(users);
    readAdmins(admins);
    readPets(pets);
    readAdoptionRequests(adoptionRequests);
    readNotification(not_vector);
    readfavourites(fav);
}

void saveAllData() {
    writeUsers(users);
    writeAdmins(admins);
    writePets(pets);
    writeAdoptionRequests(adoptionRequests);
    writeNotification(not_vector);
    writefavourites(fav);
}

void writeUsers(const vector<User>& users) {
    ofstream out(USER_FILE);
    if (!out) {
        cerr << "Error opening file " << USER_FILE << endl;
        return;
    }

    for (const auto& user : users) {
        out << user.id << " "
            << user.name << " "
            << user.email << " "
            << user.password << " "
            << user.phone << " "
            << user.role << " "
            << user.requestcounter;

        for (const auto& reqId : user.adoptionRequestIds) {
            out << " " << reqId;
        }
        out << endl;
    }
    out.close();
}

void readUsers(vector<User>& users) {
    ifstream in(USER_FILE);
    if (!in) {
        return; // File doesn't exist yet
    }

    users.clear();
    string line;

    while (getline(in, line)) {
        if (line.empty()) continue;

        istringstream iss(line);
        User temp;
        if (iss >> temp.id >> temp.name >> temp.email >> temp.password
            >> temp.phone >> temp.role >> temp.requestcounter) {

            temp.adoptionRequestIds.clear();
            string reqId;
            for (int i = 0; i < temp.requestcounter && iss >> reqId; i++) {
                temp.adoptionRequestIds.push_back(reqId);
            }
            users.push_back(temp);
        }
    }
    in.close();
}

void writeAdmins(const vector<Admin>& admins) {
    ofstream out(ADMIN_FILE);
    if (!out) {
        cerr << "Error opening file " << ADMIN_FILE << endl;
        return;
    }

    for (const auto& admin : admins) {
        out << admin.admin_id << " "
            << admin.name << " "
            << admin.email << " "
            << admin.password << " "
            << admin.phone << endl;
    }
    out.close();
}

void readAdmins(vector<Admin>& admins) {
    ifstream in(ADMIN_FILE);
    if (!in) {
        return; // File doesn't exist yet
    }

    admins.clear();
    Admin temp;
    while (in >> temp.admin_id >> temp.name >> temp.email
        >> temp.password >> temp.phone) {
        admins.push_back(temp);
    }
    in.close();
}

void writePets(const vector<Pet>& pets) {

    ofstream out(PET_FILE);
    if (!out) {
        cerr << "Error opening file " << PET_FILE << endl;
        return;
    }

    for (const auto& pet : pets) {

        //handle spaces in path
        string path = pet.image_path;
        for (int j = 0; j < path.size(); j++) {
            if (path[j] == ' ') {
                path[j] = '*';
            }
        }

        // Handle spaces in age
        string year = pet.age;
        for (int j = 0; j < year.size(); j++) {
            if (year[j] == ' ') {
                year[j] = '*';
            }
        }


        out << pet.id << " "
            << pet.name << " "
            << pet.breed << " "
            << pet.species << " "
            << pet.health << " "
            << pet.availability << " "
            << year <<" "
            <<path<<endl;
    }
    out.close();
}

void readPets(vector<Pet>& pets) {
    ifstream in(PET_FILE);
    if (!in) {
        // Initialize with default pets if file doesn't exist
        pets = {
            {"petia_1","moro","golden","dogs","vaccinated","available","2*years","moro2.jpg"},
            {"petia_2","freska","lulu","dogs","unvaccinated","available","3*months","freska.jpg"},
            {"petia_3","bonita","persian","cats","injured","available","3*years","bonita1.png"},
            {"petia_4","luna","himalayan","cats","vaccinated","available","6*months","luna.jpg"},
            {"petia_5","bondok","german","dogs","vaccinated","available","3*months","bondok.jpg"},
            {"petia_6","angel","cockatoo","birds","healthy","available","2*years","angel.jpg"},
            {"petia_7","sultan","cockatoo","birds","injured","available","3*7years","sultan.jpg"}
        };
        return;
    }

    pets.clear();
    Pet temp;
    while (in >> temp.id >> temp.name >> temp.breed >> temp.species
        >> temp.health >> temp.availability >> temp.age >> temp.image_path) {
        pets.push_back(temp);
    }
    in.close();
}

void writeAdoptionRequests(const vector<AdoptionRequest>& adoptionRequests) {
    ofstream out(REQUEST_FILE);
    if (!out) {
        cerr << "Error opening file " << REQUEST_FILE << endl;
        return;
    }

    for (const auto& req : adoptionRequests) {
        out << req.request_id << " "
            << req.user_id << " "
            << req.pet_id << " "
            << req.status << " "
            << req.score << " "
            << req.date << endl;
    }
    out.close();
}

void readAdoptionRequests(vector<AdoptionRequest>& adoptionRequests) {
    ifstream in(REQUEST_FILE);
    if (!in) {
        return; // File doesn't exist yet
    }

    adoptionRequests.clear();
    AdoptionRequest temp;
    while (in >> temp.request_id >> temp.user_id >> temp.pet_id
        >> temp.status >> temp.score >> temp.date) {
        adoptionRequests.push_back(temp);
    }
    in.close();
}

void writeNotification(const vector<thisnotification> &not_vector) {
    ofstream out(NOTIFICATION_FILE);
    if (!out) {
        cerr << "Error opening file " << NOTIFICATION_FILE << endl;
        return;
    }

    for (const auto& notification : not_vector) {
        out << notification.decision << " "
            << notification.pet_id << " "
            << notification.user_id<<endl;
    }

    out.close();
}

void readNotification( vector<thisnotification>& not_vector) {
    ifstream in(NOTIFICATION_FILE);
    if (!in) {
        return; // File doesn't exist yet
    }

    not_vector.clear();
    thisnotification temp;
    while (in >> temp.decision >> temp.pet_id
        >> temp.user_id) {
        not_vector.push_back(temp);
    }
    in.close();
}

void writefavourites(const vector<favourite>&fav) {
    ofstream out(FAVOURITE_FILE);
    if (!out) {
        cerr << "Error opening file " << FAVOURITE_FILE << endl;
        return;
    }

    for (const auto& favorite : fav) {
        out << favorite.id << " "
            << favorite.name << " "
            << favorite.user_id << " "
            << favorite.path << endl;

    }

    out.close();
}

void readfavourites (vector<favourite>& fav) {
    ifstream in(FAVOURITE_FILE);
    if (!in) {
        return; // File doesn't exist yet
    }

    fav.clear();
    favourite temp;
    while (in >> temp.id >> temp.name >> temp.user_id
        >> temp.path) {
        fav.push_back(temp);
    }
    in.close();
}

// Checking functions
void drawClippedText(sf::RenderWindow& window, const sf::Text& text, const sf::Sprite& box) {
    // 1. Save the current view
    sf::View originalView = window.getView();

    // 2. Get the bounds of the box sprite
    sf::FloatRect boxBounds = box.getGlobalBounds();

    // 3. Create a clipping view that matches our box
    sf::View clipView(boxBounds);

    // 4. Convert to viewport coordinates (0-1 range)
    clipView.setViewport(sf::FloatRect(
        boxBounds.left / window.getSize().x,
        boxBounds.top / window.getSize().y,
        (boxBounds.width / window.getSize().x) - 0.02,
        boxBounds.height / window.getSize().y
    ));

    // 5. Apply the clipping view
    window.setView(clipView);

    // 6. Draw the text (will be clipped to the box)
    window.draw(text);

    // 7. Restore the original view
    window.setView(originalView);
}
void added(string word, int x, int y) {
    RenderWindow errorwindow(VideoMode(400, 200), "SUCCESS", sf::Style::Titlebar | sf::Style::Close);
    Font font;
    Text inerror;
    Texture back_err_tex;
    Sprite back_err;
    if (!font.loadFromFile("Prototype.ttf")) {
        cout << "Failed to load font\n";
    }
    if (!back_err_tex.loadFromFile("back_error.png")) {
        cout << "Failed to load button\n";
    }

    inerror.setFont(font);
    inerror.setString(word);
    inerror.setCharacterSize(35);
    inerror.setFillColor(Color(70, 40, 10));
    inerror.setPosition(x, y);


    back_err.setTexture(back_err_tex);
    RectangleShape ok_button(sf::Vector2f(100, 40));
    ok_button.setPosition(150, 120);
    ok_button.setFillColor(sf::Color(70, 40, 10));

    sf::Text okButtonText;
    okButtonText.setFont(font);
    okButtonText.setString("OK");
    okButtonText.setCharacterSize(20);
    okButtonText.setFillColor(sf::Color::White);
    okButtonText.setPosition(185, 125);

    while (errorwindow.isOpen()) {
        Event event;
        while (errorwindow.pollEvent(event)) {
            if (event.type == Event::Closed) {
                errorwindow.close();
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                if (ok_button.getGlobalBounds().contains(mousePos)) {
                    errorwindow.close();
                }

            }
        }
        errorwindow.clear();
        errorwindow.draw(back_err);
        errorwindow.draw(inerror);
        errorwindow.draw(ok_button);
        errorwindow.draw(okButtonText);
        errorwindow.display();
    }

}
string checkvalid(string email, string password) {
    if (selection == "admin") {
        for (int i = 0;i < admins.size();i++) {
            if (admins[i].email == email && admins[i].password == password) {
                cout << "in validation" << endl;
                cout << "the email is " << email << endl;
                cout << "the pass is " << password << endl;
                return "valid";
            }
        }
        return "not";

    }
    else if (selection == "user") {
        for (int i = 0;i < users.size();i++) {
            if (users[i].email == email && users[i].password == password) {
                userid_adoption = users[i].id;
                return "valid";
            }
        }
        return "not";

    }
}
void errorbox(string text, int x, int y) {
    RenderWindow errorwindow(VideoMode(400, 200), "ERROR!!!", sf::Style::Titlebar | sf::Style::Close);
    Font font;
    Text inerror;
    Texture back_err_tex;
    Sprite back_err;
    if (!font.loadFromFile("Prototype.ttf")) {
        cout << "Failed to load font\n";
    }
    if (!back_err_tex.loadFromFile("back_error.png")) {
        cout << "Failed to load button\n";
    }

    inerror.setFont(font);
    inerror.setString(text);
    inerror.setCharacterSize(30);
    inerror.setFillColor(Color(70, 40, 10));
    inerror.setPosition(x, y);


    back_err.setTexture(back_err_tex);
    RectangleShape ok_button(sf::Vector2f(100, 40));
    ok_button.setPosition(150, 120);
    ok_button.setFillColor(sf::Color(70, 40, 10));

    sf::Text okButtonText;
    okButtonText.setFont(font);
    okButtonText.setString("OK");
    okButtonText.setCharacterSize(20);
    okButtonText.setFillColor(sf::Color::White);
    okButtonText.setPosition(185, 125);

    while (errorwindow.isOpen()) {
        Event event;
        while (errorwindow.pollEvent(event)) {
            if (event.type == Event::Closed) {
                errorwindow.close();
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                if (ok_button.getGlobalBounds().contains(mousePos)) {
                    errorwindow.close();
                }

            }
        }
        errorwindow.clear();
        errorwindow.draw(back_err);
        errorwindow.draw(inerror);
        errorwindow.draw(ok_button);
        errorwindow.draw(okButtonText);
        errorwindow.display();
    }


}
bool ckeck_email_regis(string email) {
    if (selection == "user") {
        for (int i = 0;i < users.size();i++) {
            if (email == users[i].email) {
                return false;
            }
        }
        return true;
    }
    if (selection == "admin") {
        for (int i = 0;i < admins.size();i++) {
            if (email == admins[i].email) {
                return false;
            }
        }
        return true;
    }
}
bool check_pass_regis(string pass) {
    if (selection == "user") {
        for (int i = 0;i < users.size();i++) {
            if (pass == users[i].password) {
                return false;
            }
        }
        return true;
    }
    if (selection == "admin") {
        for (int i = 0;i < admins.size();i++) {
            if (pass == admins[i].password) {
                return false;
            }
        }
        return true;
    }
}
bool check_gmail(string email) {
    string last = "";
    string target = "@gmail.com";
    if (email.size() < 10)return false;
    for (int i = 0; i < target.size(); i++) {
        last += email[email.size() - target.size() + i];
    }
    cout << "this is last digits" << last;

    if (last == "@gmail.com") {
        return true;
    }
    else {
        return false;
    }
}

// Login page
void makelogInpage() {

    if (!tex_logInbackground.loadFromFile("login_back.png")) {
        cout << "Failed to load background\n";
    }
    if (!write_button.loadFromFile("write_button.png")) {
        cout << "Failed to load write_button\n";
    }
    if (!buttontex.loadFromFile("button.png")) {
        cout << "Failed to load button\n";
    }
    if (!font.loadFromFile("spring-egg.regular.ttf")) {
        cout << "Failed to load font\n";
    }
    if (!eyetex.loadFromFile("eye3.png")) {
        cout << "Failed to load button\n";
    }
    if (!eye_closed_tex.loadFromFile("eye_no.png")) {
        cout << "Failed to load button\n";
    }

    if (!back_tex.loadFromFile("back.png")) {
        cout << "Failed to load button\n";
    }
    if (!account_tex.loadFromFile("account.png")) {
        cout << "Failed to load button\n";
    }
    account.setTexture(account_tex);
    account.setPosition(395, 735);
    account.setScale(0.2, 0.2);


    back_sp.setTexture(back_tex);
    back_sp.setScale(0.35, 0.35);
    back_sp.setPosition(1200, 20);

    eye.setTexture(eyetex);
    eye.setPosition(925, 555);
    eye.setScale(0.2, 0.2);

    eye_closed.setTexture(eye_closed_tex);
    eye_closed.setPosition(925, 555);
    eye_closed.setScale(0.2, 0.2);

    spr_logInbackground.setTexture(tex_logInbackground);

    emailValue.setTexture(write_button);
    passwordValue.setTexture(write_button);
    emailValue.setPosition(520, 380);
    passwordValue.setPosition(520, 520);

    confirmbutton.setTexture(buttontex);
    confirmbutton.setPosition(520, 650);
    confirmbutton.setScale(0.6, 0.6);

    registerbutton.setTexture(buttontex);
    registerbutton.setPosition(550, 730);
    registerbutton.setScale(0.6, 0.6);


    Login.setFont(font);
    Login.setString("log in");
    Login.setCharacterSize(60);
    Login.setPosition(545, 270);

    email.setFont(font);
    email.setString("email:");
    email.setCharacterSize(40);
    email.setPosition(300, 415);

    password.setFont(font);
    password.setString("password:");
    password.setCharacterSize(40);
    password.setPosition(255, 555);

    confirm.setFont(font);
    confirm.setString("confirm");
    confirm.setCharacterSize(20);
    confirm.setPosition(600, 670);

    Register.setFont(font);
    Register.setString("Register");
    Register.setCharacterSize(20);
    Register.setPosition(630, 750);


    emailText.setFont(font);
    emailText.setCharacterSize(30);
    emailText.setFillColor(Color::Black);
    emailText.setPosition(530, 385);

    passwordText.setFont(font);
    passwordText.setCharacterSize(30);
    passwordText.setFillColor(Color::Black);
    passwordText.setPosition(530, 525);
}
void drawlogInpage() {
    window.draw(spr_logInbackground);
    window.draw(emailValue);
    window.draw(passwordValue);
   // window.draw(registerbutton);
    window.draw(confirmbutton);
    window.draw(Login);
    window.draw(email);
    window.draw(password);
   // window.draw(Register);
    window.draw(confirm);
    window.draw(emailText);
    window.draw(passwordText);

    window.draw(account);

    if (isPasswordVisible) {
        window.draw(eye);
    }
    else
        window.draw(eye_closed);
    window.draw(back_sp);
}
void loginpage() {
    makelogInpage();
  //  bool isPasswordVisible = false;
    emailRInput = "";
    phonenumRInput = "";
    nameInput = "";
    passwordRInput = "";
    idInput = "";
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();


            if (event.type == Event::MouseButtonPressed) {
                Vector2i mousePos = Mouse::getPosition(window);
                if (eye.getGlobalBounds().contains(mousePos.x, mousePos.y)|| eye_closed.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                   isPasswordVisible = !isPasswordVisible;
                }


                if (emailValue.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    isEmailSelected = true;
                    isPasswordSelected = false;
                }
                else if (passwordValue.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    isEmailSelected = false;
                    isPasswordSelected = true;
                }
                else {
                    isEmailSelected = false;
                    isPasswordSelected = false;
                }

                if (confirmbutton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    if (!emailInput.empty() && !passwordInput.empty()) {


                        string validation = checkvalid(emailInput, passwordInput);
                        cout << "the validation string is " << validation << endl;
                        if (validation == "valid") {
                            passwordInput = "";
                            emailInput = "";
                            passwordText.setString(passwordInput);
                            emailText.setString(emailInput);

                            if (selection == "user") page_user();
                            else if (selection == "admin") adminpage();
                        }
                        else {
                            cout << "invalid email or password" << endl;
                            errorbox("INVALID email or password", 30, 50);
                        }
                    }
                    else {

                        cout << "Please fill in all fields" << endl;
                        errorbox("ENTER ALL FIELDS", 50, 50);
                    }
                }

                if (account.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    if (selection == "user") {
                        passwordInput = "";
                        emailInput = "";
                        passwordText.setString(passwordInput);
                        emailText.setString(emailInput);

                        registerationPage();

                    }
                    else if (selection == "admin") {
                        passwordInput = "";
                        emailInput = "";
                        passwordText.setString(passwordInput);
                        emailText.setString(emailInput);

                        athentication_page();
                    }
                }

                if (back_sp.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    passwordInput = "";
                    emailInput = "";
                    passwordText.setString(passwordInput);
                    emailText.setString(emailInput);
                    firstpage();
                }

            }
            //TO SHOW PASSSS
            if (!isPasswordVisible) {
                string masked(passwordInput.length(), '*');
                passwordText.setString(masked);

                //to center the pass
                FloatRect passBounds = passwordText.getLocalBounds();
                passwordText.setOrigin(passBounds.left + passBounds.width / 2.0f, passBounds.top + passBounds.height / 2.0f);
                passwordText.setPosition(passwordValue.getPosition().x + passwordValue.getGlobalBounds().width / 2.0f,
                    passwordValue.getPosition().y + passwordValue.getGlobalBounds().height / 2.0f);

            }
            else {
                passwordText.setString(passwordInput);
                // to center the pass
                FloatRect passBounds = passwordText.getLocalBounds();
                passwordText.setOrigin(passBounds.left + passBounds.width / 2.0f, passBounds.top + passBounds.height / 2.0f);
                passwordText.setPosition(passwordValue.getPosition().x + passwordValue.getGlobalBounds().width / 2.0f,
                    passwordValue.getPosition().y + passwordValue.getGlobalBounds().height / 2.0f);
            }

            if (event.type == Event::TextEntered) {
                if (event.text.unicode < 128) {
                    char enteredChar = static_cast<char>(event.text.unicode);

                    if (isEmailSelected) {
                        if (enteredChar == 8 && !emailInput.empty())  // Backspace
                            emailInput.pop_back();
                        else if (isprint(enteredChar))
                            emailInput += enteredChar;
                        emailText.setString(emailInput);


                        FloatRect emailBounds = emailText.getLocalBounds();
                        emailText.setOrigin(emailBounds.left + emailBounds.width / 2.0f, emailBounds.top + emailBounds.height / 2.0f);
                        emailText.setPosition(emailValue.getPosition().x + emailValue.getGlobalBounds().width / 2.0f,
                            emailValue.getPosition().y + emailValue.getGlobalBounds().height / 2.0f);
                    }
                    else if (isPasswordSelected) {
                        if (enteredChar == 8 && !passwordInput.empty())
                            passwordInput.pop_back();
                        else if (isprint(enteredChar))
                            passwordInput += enteredChar;


                        FloatRect passBounds = passwordText.getLocalBounds();
                        passwordText.setOrigin(passBounds.left + passBounds.width / 2.0f, passBounds.top + passBounds.height / 2.0f);
                        passwordText.setPosition(passwordValue.getPosition().x + passwordValue.getGlobalBounds().width / 2.0f,
                            passwordValue.getPosition().y + passwordValue.getGlobalBounds().height / 2.0f);
                    }




                }
            }
        }

        window.clear();
        drawlogInpage();
        window.display();
    }
}

// Regististration pages
void athentication_page() {
    const string pass_admins = "2025_admins_petia";
    string input_pass = "";

    if (!background_authen_tex.loadFromFile("back_authen.png")) {
        cout << "Failed to load background\n";
    }
    if (!danger_tex.loadFromFile("danger1.png")) {
        cout << "Failed to load background\n";
    }
    if (!authen_button_tex.loadFromFile("button.png")) {
        cout << "Failed to load background\n";
    }
    if (!font.loadFromFile("spring-egg.regular.ttf")) {
        cout << "Failed to load font\n";
    }
    if (!back_tex.loadFromFile("back.png")) {
        cout << "Failed to load button\n";
    }

    back_sp.setTexture(back_tex);
    back_sp.setScale(0.35, 0.35);
    back_sp.setPosition(1200, 20);

    background_authen.setTexture(background_authen_tex);

    danger.setTexture(danger_tex);
    danger.setScale(0.7, 0.7);
    danger.setPosition(895, 225);

    authen_button.setTexture(authen_button_tex);
    authen_button.setScale(0.8, 0.8);
    authen_button.setPosition(450, 615);

    authen.setFont(font);
    authen.setString("authentication");
    authen.setCharacterSize(60);
    authen.setPosition(310, 240);
    authen.setStyle(Text::Bold);
    authen.setFillColor(sf::Color(70, 40, 10));

    ok_athen.setFont(font);
    ok_athen.setString("okay");
    ok_athen.setCharacterSize(40);
    ok_athen.setPosition(575, 635);


    enter_authen.setFont(font);
    enter_authen.setString("ENTER THE UNIFIED PASSWORD");
    enter_authen.setCharacterSize(40);
    enter_authen.setPosition(292, 410);
    // enter_authen.setStyle(Text::Bold);

    authen_pass.setFont(font);
    authen_pass.setString(input_pass);
    authen_pass.setCharacterSize(40);
    authen_pass.setPosition(400, 510);
    authen_pass.setFillColor(Color::Black);


    while (window.isOpen()) {
        Event event;

        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::MouseButtonPressed) {
                Vector2i mousePos = Mouse::getPosition(window);
                if (authen_button.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    if (input_pass == pass_admins) {
                        register_adminPage();
                    }
                    else if (input_pass == "") {
                        errorbox("ENTER password !", 75, 50);
                    }
                    else {
                        errorbox("WRONG password !", 75, 50);
                    }

                }
                if (back_sp.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    loginpage();
                }

            }
            if (event.type == Event::TextEntered) {
                if (event.text.unicode < 128) {
                    char enteredChar = static_cast<char>(event.text.unicode);
                    if (enteredChar == 8 && !input_pass.empty())
                        input_pass.pop_back();
                    else if (isprint(enteredChar))
                        input_pass += enteredChar;
                    authen_pass.setString(input_pass);


                }
            }

        }
        window.clear();
        window.draw(background_authen);
        window.draw(danger);
        window.draw(authen_button);
        window.draw(authen_pass);
        window.draw(ok_athen);
        window.draw(authen);
        window.draw(enter_authen);
        window.draw(back_sp);
        window.display();
    }

}
void centerTextInBox(Text& text, const FloatRect& box) {
    FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);
    text.setPosition(box.left + box.width / 2, box.top + box.height / 2);
}
void makeregister_adminPage() {

    if (!tex_registerationback.loadFromFile("back_register.png")) {
        cout << "Failed to load background\n";
    }
    if (!write_button.loadFromFile("write_button.png")) {
        cout << "Failed to load valuebutton\n";
    }
    if (!font.loadFromFile("spring-egg.regular.ttf")) {
        cout << "Failed to load font\n";
    }
    if (!buttontex.loadFromFile("button.png")) {
        cout << "Failed to load button\n";
    }
    if (!back_tex.loadFromFile("back.png")) {
        cout << "Failed to load button\n";
    }

    back_sp.setTexture(back_tex);
    back_sp.setScale(0.35, 0.35);
    back_sp.setPosition(1200, 20);

    spr_registerationback.setTexture(tex_registerationback);

    namevalue.setTexture(write_button);
    namevalue.setPosition(250, 360);
    namevalue.setScale(0.7, 0.7);

    idvalue.setTexture(write_button);
    //idvalue.setPosition(900, 360);
    idvalue.setScale(0.7, 0.7);
    idvalue.setPosition(250, 460);

    emailRvalue.setTexture(write_button);
    // emailRvalue.setPosition(250, 460);
    emailRvalue.setScale(0.7, 0.7);
    emailRvalue.setPosition(250, 560);

    passwordRvalue.setTexture(write_button);
    passwordRvalue.setPosition(900, 460);
    passwordRvalue.setScale(0.7, 0.7);

    phonenumvalue.setTexture(write_button);
    // phonenumvalue.setPosition(250, 560);
    phonenumvalue.setScale(0.7, 0.7);
    phonenumvalue.setPosition(900, 360);

    signupbutton2.setTexture(buttontex);
    signupbutton2.setPosition(460, 680);
    signupbutton2.setScale(0.8, 0.8);


    userRegisteration.setFont(font);
    userRegisteration.setString("admin registration");
    userRegisteration.setCharacterSize(50);
    userRegisteration.setPosition(353, 265);
    userRegisteration.setStyle(Text::Bold);

    name.setFont(font);
    name.setString("name:");
    name.setCharacterSize(40);
    name.setPosition(100, 385);

    id.setFont(font);
    id.setString("id:");
    id.setCharacterSize(40);
    id.setPosition(150, 485);

    phonenum.setFont(font);
    phonenum.setString("phonenum:");
    phonenum.setCharacterSize(40);
    phonenum.setPosition(630, 385);

    email.setFont(font);
    email.setString("email:");
    email.setCharacterSize(40);
    email.setPosition(100, 585);

    password.setFont(font);
    password.setString("password:");
    password.setCharacterSize(40);
    password.setPosition(630, 485);

    signup2.setFont(font);
    signup2.setString("Sign up");
    signup2.setCharacterSize(40);
    signup2.setPosition(560, 703);

    nameText.setFont(font);
    nameText.setCharacterSize(30);
    nameText.setFillColor(Color::Black);
    nameText.setPosition(250, 360);
    idText.setFont(font);

    idText.setCharacterSize(30);
    idText.setFillColor(Color::Black);
    //  idText.setPosition(900, 360);
    idText.setPosition(250, 460);

    emailRText.setFont(font);
    emailRText.setCharacterSize(30);
    emailRText.setFillColor(Color::Black);
    // emailRText.setPosition(250, 460);
    emailRText.setPosition(250, 560);

    passwordRText.setFont(font);
    passwordRText.setCharacterSize(30);
    passwordRText.setFillColor(Color::Black);
    //  passwordRText.setPosition(900, 460);
    passwordRText.setPosition(900, 460);

    phonenumRText.setFont(font);
    phonenumRText.setCharacterSize(30);
    phonenumRText.setFillColor(Color::Black);
    //  phonenumRText.setPosition(250, 560);
    phonenumRText.setPosition(900, 360);

}
void drawRegisteration_Admin() {
    window.draw(spr_registerationback);
    window.draw(namevalue);
    window.draw(idvalue);
    window.draw(emailRvalue);
    window.draw(passwordRvalue);
    window.draw(phonenumvalue);
    window.draw(userRegisteration);
    window.draw(name);
    window.draw(id);
    window.draw(phonenum);
    window.draw(email);
    window.draw(password);
    window.draw(signupbutton2);
    window.draw(signup2);
    window.draw(back_sp);

    centerTextInBox(nameText, namevalue.getGlobalBounds());
    centerTextInBox(idText, idvalue.getGlobalBounds());
    centerTextInBox(emailRText, emailRvalue.getGlobalBounds());
    centerTextInBox(passwordRText, passwordRvalue.getGlobalBounds());
    centerTextInBox(phonenumRText, phonenumvalue.getGlobalBounds());
    window.draw(nameText);
    window.draw(idText);
    window.draw(emailRText);
    window.draw(passwordRText);
    window.draw(phonenumRText);
}
void register_adminPage() {

    makeregister_adminPage();
    Admin thisadmin;
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::MouseButtonPressed) {
                Vector2i mousePos = Mouse::getPosition(window);
                if (namevalue.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    isNameSelected = true;
                    isIdSelected = false;
                    isEmailRSelected = false;
                    isPasswordRSelected = false;
                    isPhoneNumSelected = false;
                }
                else if (idvalue.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    isNameSelected = false;
                    isIdSelected = true;
                    isEmailRSelected = false;
                    isPasswordRSelected = false;
                    isPhoneNumSelected = false;
                }
                else if (emailRvalue.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    isNameSelected = false;
                    isIdSelected = false;
                    isEmailRSelected = true;
                    isPasswordRSelected = false;
                    isPhoneNumSelected = false;
                }
                else if (passwordRvalue.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    isNameSelected = false;
                    isIdSelected = false;
                    isEmailRSelected = false;
                    isPasswordRSelected = true;
                    isPhoneNumSelected = false;
                }
                else if (phonenumvalue.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    isNameSelected = false;
                    isIdSelected = false;
                    isEmailRSelected = false;
                    isPasswordRSelected = false;
                    isPhoneNumSelected = true;
                }
                else {
                    isNameSelected = false;
                    isIdSelected = false;
                    isEmailRSelected = false;
                    isPasswordRSelected = false;
                    isPhoneNumSelected = false;
                }
                if (back_sp.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    emailRInput = "";
                    phonenumRInput = "";
                    nameInput = "";
                    passwordRInput = "";
                    idInput = "";
                    nameText.setString(nameInput);
                    idText.setString(idInput);
                    emailRText.setString(emailRInput);
                    passwordRText.setString(passwordRInput);
                    phonenumRText.setString(phonenumRInput);

                    loginpage();
                }

                if (signupbutton2.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    int n = stoi(idInput);
                    ///thisuser.id = to_string(n);
                    if (nameInput == "" || passwordRInput == "" || phonenumRInput == "" || emailRInput == "" || idInput == "") {
                        errorbox("ENTER ALL INPUTS !!!", 65, 50);
                    }
                    else if (phonenumRInput.size() != 11) {
                        errorbox("phone number must be\n11 digits !", 50, 30);
                    }
                    else if (phonenumRInput[0] != '0' || phonenumRInput[1] != '1') {
                        errorbox("INVALID phone number !", 50, 50);
                    }
                    else if (!check_gmail(emailRInput)) {
                        errorbox("INVALID email !", 105, 50);
                    }
                    else if (passwordRInput.size() != 8) {
                        errorbox("password must be 8 digits", 25, 50);
                    }
                    else if (!ckeck_email_regis(emailRInput)) {
                        errorbox("UNAVAILABLE email !", 50, 50);
                    }
                    else if (!check_pass_regis(passwordRInput)) {
                        errorbox("UNAVAILABLE password !", 38, 50);
                    }
                    else if (n <= 1000) {
                        errorbox("ID must be 100X format !", 38, 50);
                    }
                    else {
                        cout << "the inputs are" << endl;
                        cout << "id is " << idInput << endl;
                        cout << "name is " << nameInput << endl;
                        cout << "pass is " << passwordRInput << endl;
                        cout << "phone is " << phonenumRInput << endl;
                        cout << "the email is " << emailRInput << endl;

                        thisadmin.admin_id = idInput;
                        thisadmin.email = emailRInput;
                        thisadmin.name = nameInput;
                        thisadmin.password = passwordRInput;
                        thisadmin.phone = phonenumRInput;
                        admins.push_back(thisadmin);
                        saveAllData();

                        emailRInput = "";
                        phonenumRInput = "";
                        nameInput = "";
                        passwordRInput = "";
                        idInput = "";
                        thisadmin.admin_id = "";
                        thisadmin.email = "";
                        thisadmin.name = "";
                        thisadmin.password = "";
                        thisadmin.phone = "";
                        nameText.setString(nameInput);
                        idText.setString(idInput);
                        emailRText.setString(emailRInput);
                        passwordRText.setString(passwordRInput);
                        phonenumRText.setString(phonenumRInput);
                        loginpage();
                    }
                }
            }

            if (event.type == Event::TextEntered) {
                if (event.text.unicode < 128) {
                    char enteredChar = static_cast<char>(event.text.unicode);
                    //cout << "entered" << endl;
                    if (isNameSelected) {
                        if (enteredChar == 8 && !nameInput.empty())
                            nameInput.pop_back();
                        else if (isprint(enteredChar))
                            nameInput += enteredChar;
                        nameText.setString(nameInput);
                    }
                    if (isIdSelected) {
                        if (enteredChar == 8 && !idInput.empty())
                            idInput.pop_back();
                        else if (isprint(enteredChar))
                            idInput += enteredChar;
                        idText.setString(idInput);
                    }
                    if (isEmailRSelected) {
                        if (enteredChar == 8 && !emailRInput.empty())
                            emailRInput.pop_back();
                        else if (isprint(enteredChar))
                            emailRInput += enteredChar;
                        emailRText.setString(emailRInput);
                    }
                    if (isPasswordRSelected) {
                        if (enteredChar == 8 && !passwordRInput.empty())
                            passwordRInput.pop_back();
                        else if (isprint(enteredChar))
                            passwordRInput += enteredChar;
                        // string masked(passwordRInput.length(), '*');
                        passwordRText.setString(passwordRInput);
                    }
                    if (isPhoneNumSelected) {
                        if (enteredChar == 8 && !phonenumRInput.empty())
                            phonenumRInput.pop_back();
                        else if (isprint(enteredChar))
                            phonenumRInput += enteredChar;
                        phonenumRText.setString(phonenumRInput);
                    }
                }
            }


            window.clear();
            drawRegisteration_Admin();
            window.display();
        }


    }
}
void makeregisterationPage() {

    if (!tex_registerationback.loadFromFile("back_register.png")) {
        cout << "Failed to load background\n";
    }
    if (!write_button.loadFromFile("write_button.png")) {
        cout << "Failed to load valuebutton\n";
    }
    if (!buttontex.loadFromFile("button.png")) {
        cout << "Failed to load button\n";
    }
    if (!font.loadFromFile("spring-egg.regular.ttf")) {
        cout << "Failed to load font\n";
    }

    if (!back_tex.loadFromFile("back.png")) {
        cout << "Failed to load button\n";
    }

    back_sp.setTexture(back_tex);
    back_sp.setScale(0.35, 0.35);
    back_sp.setPosition(1200, 20);

    spr_registerationback.setTexture(tex_registerationback);

    namevalue.setTexture(write_button);
    namevalue.setPosition(250, 360);
    namevalue.setScale(0.7, 0.7);

    idvalue.setTexture(write_button);
    // idvalue.setScale(0.7, 0.7);
    // idvalue.setPosition(250, 460);

    emailRvalue.setTexture(write_button);
    emailRvalue.setScale(0.7, 0.7);
    // emailRvalue.setPosition(250, 560);
    emailRvalue.setPosition(250, 460);


    passwordRvalue.setTexture(write_button);
    passwordRvalue.setScale(0.7, 0.7);
    // passwordRvalue.setPosition(900, 560);
    passwordRvalue.setPosition(900, 460);

    phonenumvalue.setTexture(write_button);
    phonenumvalue.setScale(0.7, 0.7);
    phonenumvalue.setPosition(900, 360);

    rolevalue.setTexture(write_button);
    rolevalue.setScale(0.7, 0.7);
    // rolevalue.setPosition(900, 460);
    rolevalue.setPosition(250, 560);

    signupbutton.setTexture(buttontex);
    signupbutton.setPosition(460, 680);
    signupbutton.setScale(0.8, 0.8);


    userRegisteration.setFont(font);
    userRegisteration.setString("user registration");
    userRegisteration.setCharacterSize(50);
    userRegisteration.setPosition(360, 265);
    userRegisteration.setStyle(Text::Bold);

    name.setFont(font);
    name.setString("name:");
    name.setCharacterSize(40);
    name.setPosition(100, 385);

    // id.setFont(font);
   //  id.setString("id:");
   //  id.setCharacterSize(40);
    // id.setPosition(150, 485);


    phonenum.setFont(font);
    phonenum.setString("phonenum:");
    phonenum.setCharacterSize(40);
    phonenum.setPosition(630, 385);


    role.setFont(font);
    role.setString("role:");
    role.setCharacterSize(40);
    //  role.setPosition(695, 485);
    role.setPosition(100, 585);

    email.setFont(font);
    email.setString("email:");
    email.setCharacterSize(40);
    // email.setPosition(100, 585);
    email.setPosition(100, 485);

    password.setFont(font);
    password.setString("password:");
    password.setCharacterSize(40);
    // password.setPosition(630, 585);
    password.setPosition(630, 485);

    signup.setFont(font);
    signup.setString("Sign up");
    signup.setCharacterSize(40);
    signup.setPosition(560, 703);


    nameText.setFont(font);
    nameText.setCharacterSize(30);
    nameText.setFillColor(Color::Black);
    nameText.setPosition(250, 360);

    idText.setFont(font);
    idText.setCharacterSize(30);
    idText.setFillColor(Color::Black);
    idText.setPosition(900, 360);

    emailRText.setFont(font);
    emailRText.setCharacterSize(30);
    emailRText.setFillColor(Color::Black);
    emailRText.setPosition(250, 460);

    passwordRText.setFont(font);
    passwordRText.setCharacterSize(30);
    passwordRText.setFillColor(Color::Black);
    passwordRText.setPosition(900, 460);

    phonenumRText.setFont(font);
    phonenumRText.setCharacterSize(30);
    phonenumRText.setFillColor(Color::Black);
    phonenumRText.setPosition(250, 560);

    roleRText.setFont(font);
    roleRText.setCharacterSize(30);
    roleRText.setFillColor(Color::Black);
    roleRText.setPosition(900, 560);


}
void drawregisterationPage() {
    window.draw(spr_registerationback);
    window.draw(namevalue);
    //  window.draw(idvalue);
    window.draw(emailRvalue);
    window.draw(passwordRvalue);
    window.draw(phonenumvalue);
    window.draw(rolevalue);
    window.draw(userRegisteration);
    window.draw(name);
    window.draw(id);
    window.draw(phonenum);
    window.draw(role);
    window.draw(email);
    window.draw(password);
    window.draw(signupbutton);
    window.draw(signup);
    window.draw(back_sp);

    centerTextInBox(nameText, namevalue.getGlobalBounds());
    centerTextInBox(idText, idvalue.getGlobalBounds());
    centerTextInBox(emailRText, emailRvalue.getGlobalBounds());
    centerTextInBox(passwordRText, passwordRvalue.getGlobalBounds());
    centerTextInBox(phonenumRText, phonenumvalue.getGlobalBounds());
    centerTextInBox(roleRText, rolevalue.getGlobalBounds());


    window.draw(nameText);
    window.draw(idText);
  ///  window.draw(emailRText);
    drawClippedText(window, emailRText, emailRvalue);
    window.draw(passwordRText);
    window.draw(phonenumRText);
    window.draw(roleRText);
}
void registerationPage() {
    makeregisterationPage();

    User thisuser;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();


            if (event.type == Event::MouseButtonPressed) {
                Vector2i mousePos = Mouse::getPosition(window);
                if (namevalue.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    isNameSelected = true;
                    isIdSelected = false;
                    isEmailRSelected = false;
                    isPasswordRSelected = false;
                    isPhoneNumSelected = false;
                    isRoleSelected = false;
                }
                else if (idvalue.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    isNameSelected = false;
                    isIdSelected = true;
                    isEmailRSelected = false;
                    isPasswordRSelected = false;
                    isPhoneNumSelected = false;
                    isRoleSelected = false;
                }
                else if (emailRvalue.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    isNameSelected = false;
                    isIdSelected = false;
                    isEmailRSelected = true;
                    isPasswordRSelected = false;
                    isPhoneNumSelected = false;
                    isRoleSelected = false;
                }
                else if (passwordRvalue.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    isNameSelected = false;
                    isIdSelected = false;
                    isEmailRSelected = false;
                    isPasswordRSelected = true;
                    isPhoneNumSelected = false;
                    isRoleSelected = false;
                }
                else if (phonenumvalue.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    isNameSelected = false;
                    isIdSelected = false;
                    isEmailRSelected = false;
                    isPasswordRSelected = false;
                    isPhoneNumSelected = true;
                    isRoleSelected = false;
                }
                else if (rolevalue.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    isNameSelected = false;
                    isIdSelected = false;
                    isEmailRSelected = false;
                    isPasswordRSelected = false;
                    isPhoneNumSelected = false;
                    isRoleSelected = true;
                }
                else {
                    isNameSelected = false;
                    isIdSelected = false;
                    isEmailRSelected = false;
                    isPasswordRSelected = false;
                    isPhoneNumSelected = false;
                    isRoleSelected = false;
                }

                if (back_sp.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    nameInput = "";
                    emailRInput = "";
                    //  idInput = "";
                    passwordRInput = "";
                    phonenumRInput = "";
                    roleRInput = "";

                    nameText.setString(nameInput);
                    //  idText.setString(idInput);
                    emailRText.setString(emailRInput);
                    passwordRText.setString(passwordRInput);
                    phonenumRText.setString(phonenumRInput);
                    roleRText.setString(roleRInput);

                    loginpage();
                }


                if (signupbutton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    for (int i = 0;i < roleRInput.size();i++) {
                        roleRInput[i] = tolower(roleRInput[i]);
                    }
                    if (nameInput == "" || passwordRInput == "" || phonenumRInput == "" || emailRInput == "" || roleRInput == "") {
                        errorbox("ENTER ALL INPUTS !!!", 65, 50);


                    }
                    else if (phonenumRInput.size() != 11) {
                        errorbox("phone number must be\n11 digits !", 50, 30);
                    }
                    else if (phonenumRInput[0] != '0' || phonenumRInput[1] != '1') {
                        errorbox("INVALID phone number !", 50, 50);
                    }
                    else if (!check_gmail(emailRInput)) {
                        errorbox("INVALID email !", 105, 50);
                    }
                    else if (passwordRInput.size() != 8) {
                        errorbox("password must be 8 digits", 25, 50);
                    }
                    else if (roleRInput != "adopter" && roleRInput != "caretaker") {
                        errorbox("       role must be\n adopter or caretaker !", 50, 30);
                    }
                    else if (!ckeck_email_regis(emailRInput)) {
                        errorbox("UNAVAILABLE email !", 50, 50);
                    }
                    else if (!check_pass_regis(passwordRInput)) {
                        errorbox("UNAVAILABLE password !", 38, 50);
                    }
                    else {
                        cout << "the inputs are" << endl;
                        cout << "id is " << idInput << endl;
                        cout << "name is " << nameInput << endl;
                        cout << "pass is " << passwordRInput << endl;
                        cout << "phone is " << phonenumRInput << endl;
                        cout << "the email is " << emailRInput << endl;
                        cout << "the role is" << roleRInput << endl;
                        if (users.empty()) {
                            thisuser.id = "1";
                        }
                        else {
                            int n = stoi(users[users.size() - 1].id) + 1;
                            thisuser.id = to_string(n);
                        }

                        added("your id is " + thisuser.id, 115, 50);

                        thisuser.name = nameInput;
                        thisuser.email = emailRInput;
                        // thisuser.id = idInput;
                        thisuser.password = passwordRInput;
                        thisuser.phone = phonenumRInput;
                        thisuser.role = roleRInput;

                        cout << "this id is " << thisuser.id << endl;

                        users.push_back(thisuser);
                        saveAllData();

                        nameInput = "";
                        emailRInput = "";
                        //  idInput = "";
                        passwordRInput = "";
                        phonenumRInput = "";
                        roleRInput = "";

                        nameText.setString(nameInput);
                        //  idText.setString(idInput);
                        emailRText.setString(emailRInput);
                        passwordRText.setString(passwordRInput);
                        phonenumRText.setString(phonenumRInput);
                        roleRText.setString(roleRInput);

                        thisuser.name = "";
                        thisuser.email = "";
                        thisuser.id = "";
                        thisuser.password = "";
                        thisuser.phone = "";
                        thisuser.role = "";

                        loginpage();
                    }
                }

            }


            if (event.type == Event::TextEntered) {
                if (event.text.unicode < 128) {
                    char enteredChar = static_cast<char>(event.text.unicode);

                    if (isNameSelected) {
                        if (enteredChar == 8 && !nameInput.empty())
                            nameInput.pop_back();
                        else if (isprint(enteredChar))
                            nameInput += enteredChar;
                        nameText.setString(nameInput);
                    }
                    else if (isIdSelected) {
                        if (enteredChar == 8 && !idInput.empty())
                            idInput.pop_back();
                        else if (isprint(enteredChar))
                            idInput += enteredChar;
                        idText.setString(idInput);
                    }
                    else if (isEmailRSelected) {
                        if (enteredChar == 8 && !emailRInput.empty())
                            emailRInput.pop_back();
                        else if (isprint(enteredChar))
                            emailRInput += enteredChar;
                        emailRText.setString(emailRInput);
                    }
                    else if (isPasswordRSelected) {
                        if (enteredChar == 8 && !passwordRInput.empty())
                            passwordRInput.pop_back();
                        else if (isprint(enteredChar))
                            passwordRInput += enteredChar;
                        passwordRText.setString(passwordRInput);
                    }
                    else if (isPhoneNumSelected) {
                        if (enteredChar == 8 && !phonenumRInput.empty())
                            phonenumRInput.pop_back();
                        else if (isprint(enteredChar))
                            phonenumRInput += enteredChar;
                        phonenumRText.setString(phonenumRInput);
                    }
                    else if (isRoleSelected) {
                        if (enteredChar == 8 && !roleRInput.empty())
                            roleRInput.pop_back();
                        else if (isprint(enteredChar))
                            roleRInput += enteredChar;
                        roleRText.setString(roleRInput);
                    }
                }
            }
        }

        window.clear();
        drawregisterationPage();
        window.display();
    }


}

// First page
void makePage_1() {
    if (!tex_background1.loadFromFile("background.png")) {
        cout << "Failed to load background\n";
    }
    if (!buttontex.loadFromFile("button.png")) {
        cout << "Failed to load button\n";
    }
    if (!font.loadFromFile("spring-egg.regular.ttf")) {
        cout << "Failed to load font\n";
    }

    spr_background1.setTexture(tex_background1);

    userbutton.setTexture(buttontex);
    adminbutton.setTexture(buttontex);
    userbutton.setPosition(400, 330);
    adminbutton.setPosition(400, 470);



    user.setFont(font);
    user.setString("user");
    user.setCharacterSize(50);
    user.setPosition(555, 357);

    admin.setFont(font);
    admin.setString("admin");
    admin.setCharacterSize(50);
    admin.setPosition(550, 500);

}
void drawPage_1() {
    window.draw(spr_background1);
    window.draw(userbutton);
    window.draw(adminbutton);
    window.draw(user);
    window.draw(admin);
}
void firstpage() {
    Mouse ms;
    makePage_1();
    while (window.isOpen()) {
        mouseRectangle.setPosition(ms.getPosition().x - 330, ms.getPosition().y - 140);
        if (mouseRectangle.getGlobalBounds().intersects(userbutton.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left)) {
            selection = "user";
            loginpage();
            // registerationPage();
        }
        if (mouseRectangle.getGlobalBounds().intersects(adminbutton.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left)) {
            selection = "admin";
            loginpage();
            //register_adminPage();
        }
        window.clear();
        drawPage_1();
        window.display();
    }
}


// ==============================================
// Admin Functions 
// ==============================================

// Add pet page
string addwindow() {
    RenderWindow errorwindow(VideoMode(400, 200), "ADDING IMAGE", sf::Style::Titlebar | sf::Style::Close);
    Font font;
    Text inerror, inputpath;
    Texture back_err_tex, imagetex;
    Sprite back_err, box_path;
    string input;
    bool select_input = false;
    if (!font.loadFromFile("Prototype.ttf")) {
        cout << "Failed to load font\n";
    }
    if (!back_err_tex.loadFromFile("back_error.png")) {
        cout << "Failed to load button\n";
    }
    if (!imagetex.loadFromFile("trans_box.png")) {
        cout << "Failed to load button\n";
    }

    box_path.setTexture(imagetex);
    box_path.setPosition(35, 60);
    box_path.setScale(0.7, 0.7);

    inputpath.setFont(font);
    inputpath.setCharacterSize(25);
    inputpath.setFillColor(sf::Color::Black);
    inputpath.setPosition(43, 73);


    inerror.setFont(font);
    inerror.setString("Enter image path :");
    inerror.setCharacterSize(30);
    inerror.setFillColor(Color(70, 40, 10));
    inerror.setPosition(38, 25);


    back_err.setTexture(back_err_tex);
    RectangleShape ok_button(sf::Vector2f(100, 40));
    ok_button.setPosition(150, 135);
    ok_button.setFillColor(sf::Color(70, 40, 10));

    sf::Text okButtonText;
    okButtonText.setFont(font);
    okButtonText.setString("OK");
    okButtonText.setCharacterSize(20);
    okButtonText.setFillColor(sf::Color::White);
    okButtonText.setPosition(185, 143);

    while (errorwindow.isOpen()) {
        Event event;
        while (errorwindow.pollEvent(event)) {
            if (event.type == Event::Closed) {
                errorwindow.close();
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                if (ok_button.getGlobalBounds().contains(mousePos)) {
                    return input;
                    errorwindow.close();
                }
                if (box_path.getGlobalBounds().contains(mousePos)) {
                    select_input = true;
                }
                else {
                    select_input = false;
                }
            }
            if (event.type == Event::TextEntered) {
                if (event.text.unicode == 22 && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
                    std::string clipboard = sf::Clipboard::getString();
                    input += clipboard;
                    inputpath.setString(input);
                }
                if (event.text.unicode < 128) {
                    char enteredChar = static_cast<char>(event.text.unicode);

                    if (select_input) {
                        if (enteredChar == 8 && !input.empty())
                            input.pop_back();
                        else if (isprint(enteredChar))
                            input += enteredChar;
                        inputpath.setString(input);
                    }
                }
            }


        }
        errorwindow.clear();
        errorwindow.draw(back_err);
        errorwindow.draw(inerror);
        errorwindow.draw(ok_button);
        errorwindow.draw(okButtonText);
        errorwindow.draw(box_path);
        drawClippedText(errorwindow, inputpath, box_path);
        //  errorwindow.draw(inputpath); 
        errorwindow.display();
    }

}
void makeaddAdmin() {
    //   Texture add_back_tex, add_button_tex, add_box_tex;
      // Sprite add_back, add_boxname,add_boxbreed,add_boxspecies,add_boxage,add_boxhealth, add_buton, add_pic_button;
       //Text p_name, p_breed, p_species, p_age, p_health, p_image, p_ok, p_addImage;
       //Text pet_name,pet_breed,pet_species, pet_age, pet_health;

    if (!add_back_tex.loadFromFile("background_add.png")) {
        cout << "Error loading back\n";
    }

    if (!font.loadFromFile("spring-egg.regular.ttf")) {
        cout << "Failed to load font\n";
    }
    if (!add_button_tex.loadFromFile("button.png")) {
        cout << "Error loading back\n";
    }
    if (!add_box_tex.loadFromFile("trans_box.png")) {
        cout << "Error loading box\n";
    }
    if (!back_tex.loadFromFile("back.png")) {
        cout << "Failed to load button\n";
    }

    back_sp.setTexture(back_tex);
    back_sp.setScale(0.35, 0.35);
    back_sp.setPosition(1200, 20);

    add_back.setTexture(add_back_tex);

    add_boxname.setTexture(add_box_tex);
    add_boxname.setPosition(540, 230);
    add_boxname.setScale(1, 1);

    add_boxbreed.setTexture(add_box_tex);
    add_boxbreed.setPosition(540, 330);
    add_boxbreed.setScale(1, 1);

    add_boxspecies.setTexture(add_box_tex);
    add_boxspecies.setPosition(540, 430);
    add_boxspecies.setScale(1, 1);

    add_boxage.setTexture(add_box_tex);
    add_boxage.setPosition(540, 530);
    add_boxage.setScale(1, 1);

    add_boxhealth.setTexture(add_box_tex);
    add_boxhealth.setPosition(540, 630);
    add_boxhealth.setScale(1, 1);

    add_buton.setTexture(add_button_tex);
    add_buton.setPosition(800, 790);
    add_buton.setScale(0.8, 0.8);

    add_pic_button.setTexture(add_button_tex);
    add_pic_button.setPosition(140, 790);
    add_pic_button.setScale(0.8, 0.8);


    p_name.setFont(font);
    p_name.setString("name :");
    p_name.setCharacterSize(45);
    p_name.setPosition(300, 250);

    p_breed.setFont(font);
    p_breed.setString("breed :");
    p_breed.setCharacterSize(45);
    p_breed.setPosition(300, 350);

    p_species.setFont(font);
    p_species.setString("species :");
    p_species.setCharacterSize(45);
    p_species.setPosition(300, 450);

    p_age.setFont(font);
    p_age.setString("age :");
    p_age.setCharacterSize(45);
    p_age.setPosition(300, 550);

    p_health.setFont(font);
    p_health.setString("health :");
    p_health.setCharacterSize(45);
    p_health.setPosition(300, 650);

    p_ok.setFont(font);
    p_ok.setString("okay");
    p_ok.setCharacterSize(30);
    p_ok.setPosition(935, 815);

    p_addImage.setFont(font);
    p_addImage.setString("add image");
    p_addImage.setCharacterSize(30);
    p_addImage.setPosition(235, 815);


    pet_name_text.setFont(font);
    pet_name_text.setCharacterSize(35);
    pet_name_text.setPosition(580, 257);
    pet_name_text.setFillColor(Color::Black);


    pet_breed_text.setFont(font);
    pet_breed_text.setCharacterSize(35);
    pet_breed_text.setPosition(580, 357);
    pet_breed_text.setFillColor(Color::Black);

    pet_species_text.setFont(font);
    pet_species_text.setCharacterSize(35);
    pet_species_text.setPosition(580, 457);
    pet_species_text.setFillColor(Color::Black);

    pet_age_text.setFont(font);
    pet_age_text.setCharacterSize(35);
    pet_age_text.setPosition(580, 557);
    pet_age_text.setFillColor(Color::Black);

    pet_health_text.setFont(font);
    pet_health_text.setCharacterSize(35);
    pet_health_text.setPosition(580, 657);
    pet_health_text.setFillColor(Color::Black);


}
void drawAddAdmin() {

    window.draw(add_back);
    window.draw(add_boxname);
    window.draw(add_boxbreed);
    window.draw(add_boxspecies);
    window.draw(add_boxage);
    window.draw(add_boxhealth);
    window.draw(add_buton);
    window.draw(add_pic_button);
    window.draw(p_name);
    window.draw(p_breed);
    window.draw(p_species);
    window.draw(p_age);
    window.draw(p_health);
    window.draw(p_ok);
    window.draw(p_addImage);
    window.draw(back_sp);

    window.draw(pet_name_text);
    window.draw(pet_breed_text);
    window.draw(pet_species_text);
    window.draw(pet_age_text);
    window.draw(pet_health_text);

}
void addadmin() {
    makeaddAdmin();
    Pet thispet;
    bool petnameselect = false, petbreedselect = false, pethealthselect = false, petspeciesselect = false, petageselect = false;
    string pet_name_in, pet_age_in, pet_health_in, pet_breed_in, pet_species_in;
    string path;
    //Text pet_name_text,pet_age_text,pet_health_text,pet_breed_text,pet_species_text;
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();


            if (event.type == Event::MouseButtonPressed) {
                Vector2i mousePos = Mouse::getPosition(window);
                if (add_boxname.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    petnameselect = true;
                    petbreedselect = false;
                    pethealthselect = false;
                    petspeciesselect = false;
                    petageselect = false;

                }
                else if (add_boxbreed.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    petnameselect = false;
                    petbreedselect = true;
                    pethealthselect = false;
                    petspeciesselect = false;
                    petageselect = false;
                }
                else if (add_boxspecies.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    petnameselect = false;
                    petbreedselect = false;
                    pethealthselect = false;
                    petspeciesselect = true;
                    petageselect = false;
                }
                else if (add_boxage.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    petnameselect = false;
                    petbreedselect = false;
                    pethealthselect = false;
                    petspeciesselect = false;
                    petageselect = true;
                }
                else if (add_boxhealth.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    petnameselect = false;
                    petbreedselect = false;
                    pethealthselect = true;
                    petspeciesselect = false;
                    petageselect = false;
                }

                else {
                    petnameselect = false;
                    petbreedselect = false;
                    pethealthselect = false;
                    petspeciesselect = false;
                    petageselect = false;
                }

                if (back_sp.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    pet_name_in = "";
                    pet_age_in = "";
                    pet_species_in = "";
                    pet_breed_in = "";
                    pet_health_in = "";
                    pet_name_text.setString(pet_name_in);
                    pet_breed_text.setString(pet_breed_in);
                    pet_health_text.setString(pet_health_in);
                    pet_species_text.setString(pet_species_in);
                    pet_age_text.setString(pet_age_in);

                    // page_user();
                   adminpage();
                }


                if (add_buton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {

                    thispet.name = pet_name_in;
                   // thispet.age = pet_age_in;
                    thispet.breed = pet_breed_in;
                    thispet.species = pet_species_in;
                    thispet.health = pet_health_in;
                    thispet.availability = "available";
                    char last = pets[pets.size() - 1].id.back();
                    string s = "";
                    s += last;
                    int n = stoi(s) + 1;
                    thispet.id = "petia_" + to_string(n);
                   // thispet.image_path = path;
                    cout << "this pet id is " << thispet.id << endl;
                    //pets.push_back(thispet);

                    ///for saving data
                    for (int i = 0;i < path.size();i++) {
                        if (path[i] == ' ') {
                            path[i] = '*';
                        }
                            
                    }
                    thispet.image_path = path;

                    for (int i = 0;i < pet_age_in.size();i++) {
                        if (pet_age_in[i] == ' ') {
                            pet_age_in[i] = '*';
                        }

                    }
                    thispet.age = pet_age_in;

                    pets.push_back(thispet);

                    writePets(pets);
                    ///
                    added("pet is added !", 100, 50);
                    pet_name_in = "";
                    pet_age_in = "";
                    pet_species_in = "";
                    pet_breed_in = "";
                    pet_health_in = "";
                    pet_name_text.setString(pet_name_in);
                    pet_breed_text.setString(pet_breed_in);
                    pet_health_text.setString(pet_health_in);
                    pet_species_text.setString(pet_species_in);
                    pet_age_text.setString(pet_age_in);
                }

                if (add_pic_button.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    path = addwindow();

                }



            }




            if (event.type == Event::TextEntered) {
                if (event.text.unicode < 128) {
                    char enteredChar = static_cast<char>(event.text.unicode);

                    if (petnameselect) {
                        if (enteredChar == 8 && !pet_name_in.empty())
                            pet_name_in.pop_back();
                        else if (isprint(enteredChar))
                            pet_name_in += enteredChar;
                        pet_name_text.setString(pet_name_in);
                    }
                    else if (petbreedselect) {
                        if (enteredChar == 8 && !pet_breed_in.empty())
                            pet_breed_in.pop_back();
                        else if (isprint(enteredChar))
                            pet_breed_in += enteredChar;
                        pet_breed_text.setString(pet_breed_in);
                    }
                    else if (pethealthselect) {
                        if (enteredChar == 8 && !pet_health_in.empty())
                            pet_health_in.pop_back();
                        else if (isprint(enteredChar))
                            pet_health_in += enteredChar;
                        pet_health_text.setString(pet_health_in);
                    }
                    else if (petspeciesselect) {
                        if (enteredChar == 8 && !pet_species_in.empty())
                            pet_species_in.pop_back();
                        else if (isprint(enteredChar))
                            pet_species_in += enteredChar;
                        pet_species_text.setString(pet_species_in);
                    }
                    else if (petageselect) {
                        if (enteredChar == 8 && !pet_age_in.empty())
                            pet_age_in.pop_back();
                        else if (isprint(enteredChar))
                            pet_age_in += enteredChar;
                        pet_age_text.setString(pet_age_in);
                    }

                }
            }

        }

        window.clear();
        drawAddAdmin();
        window.display();
    }


}

// Update pet page
void makeUpdate() {
    if (!back_edit_tex.loadFromFile("update_background.png")) {
        cout << "Failed to load background\n";
    }

    if (!font.loadFromFile("spring-egg.regular.ttf")) {
        cout << "Failed to load font\n";
    }


    edit_box_tex.loadFromFile("filled_box.png");
    button_edit_tex.loadFromFile("button.png");
    if (!back_tex.loadFromFile("back.png")) {
        cout << "Failed to load button\n";
    }

    back_sp.setTexture(back_tex);
    back_sp.setScale(0.35, 0.35);
    back_sp.setPosition(1200, 20);


    updateBOX.setTexture(button_edit_tex);
    updateBOX.setScale(0.7, 0.7);
    updateBOX.setPosition(475, 750);

    UpdateBoxText.setFont(font);
    UpdateBoxText.setString("update");
    UpdateBoxText.setCharacterSize(30);
    UpdateBoxText.setPosition(570, 770);

    back_edit.setTexture(back_edit_tex);

    name_e.setTexture(button_edit_tex);
    name_e.setScale(0.7, 0.7);
    name_e.setPosition(100, 250);

    age_e.setTexture(button_edit_tex);
    age_e.setScale(0.7, 0.7);
    age_e.setPosition(475, 250);

    health_e.setTexture(button_edit_tex);
    health_e.setScale(0.7, 0.7);
    health_e.setPosition(850, 250);

    breed_e.setTexture(button_edit_tex);
    breed_e.setScale(0.7, 0.7);
    breed_e.setPosition(260, 350);

    species_e.setTexture(button_edit_tex);
    species_e.setScale(0.7, 0.7);
    species_e.setPosition(690, 350);


    name_ed.setFont(font);
    name_ed.setString("name");
    name_ed.setCharacterSize(30);
    name_ed.setPosition(210, 270);

    age_ed.setFont(font);
    age_ed.setString("age");
    age_ed.setCharacterSize(30);
    age_ed.setPosition(600, 270);

    health_ed.setFont(font);
    health_ed.setString("health");
    health_ed.setCharacterSize(30);
    health_ed.setPosition(940, 270);

    breed_ed.setFont(font);
    breed_ed.setString("breed");
    breed_ed.setCharacterSize(30);
    breed_ed.setPosition(370, 370);

    species_ed.setFont(font);
    species_ed.setString("species");
    species_ed.setCharacterSize(30);
    species_ed.setPosition(780, 370);


    edit_box_id.setTexture(edit_box_tex);
    edit_box_id.setScale(1, 1);
    edit_box_id.setPosition(500, 520);

    edit_box.setTexture(edit_box_tex);
    edit_box.setScale(1, 1);
    edit_box.setPosition(500, 630);

    edit_id.setFont(font);
    edit_id.setString("pet id");
    edit_id.setCharacterSize(40);
    edit_id.setPosition(300, 547);
    edit_id.setFillColor(sf::Color(70, 40, 10));

    edit_name.setFont(font);
    edit_name.setString("name");
    edit_name.setCharacterSize(40);
    edit_name.setPosition(300, 655);
    edit_name.setFillColor(sf::Color(70, 40, 10));

    edit_age.setFont(font);
    edit_age.setString("age");
    edit_age.setCharacterSize(40);
    edit_age.setPosition(300, 655);
    edit_age.setFillColor(sf::Color(70, 40, 10));

    edit_health.setFont(font);
    edit_health.setString("health");
    edit_health.setCharacterSize(40);
    edit_health.setPosition(300, 655);
    edit_health.setFillColor(sf::Color(70, 40, 10));

    edit_breed.setFont(font);
    edit_breed.setString("breed");
    edit_breed.setCharacterSize(40);
    edit_breed.setPosition(300, 655);
    edit_breed.setFillColor(sf::Color(70, 40, 10));

    edit_species.setFont(font);
    edit_species.setString("species");
    edit_species.setCharacterSize(40);
    edit_species.setPosition(300, 655);
    edit_species.setFillColor(sf::Color(70, 40, 10));
    //in the boxess
    name_edit.setFont(font);
    name_edit.setCharacterSize(37);
    name_edit.setPosition(550, 660);
    name_edit.setFillColor(Color::Black);

    age_edit.setFont(font);
    age_edit.setCharacterSize(40);
    age_edit.setPosition(550, 660);
    age_edit.setFillColor(Color::Black);

    health_edit.setFont(font);
    health_edit.setCharacterSize(40);
    health_edit.setPosition(550, 660);
    health_edit.setFillColor(Color::Black);

    breed_edit.setFont(font);
    breed_edit.setCharacterSize(40);
    breed_edit.setPosition(550, 660);
    breed_edit.setFillColor(Color::Black);

    species_edit.setFont(font);
    species_edit.setCharacterSize(40);
    species_edit.setPosition(550, 660);
    species_edit.setFillColor(Color::Black);


    id_edit.setFont(font);
    id_edit.setCharacterSize(37);
    id_edit.setPosition(550, 547);
    id_edit.setFillColor(Color::Black);


}
void drawUpdate() {
    window.draw(back_edit);
    window.draw(name_e);
    window.draw(age_e);
    window.draw(health_e);
    window.draw(breed_e);
    window.draw(species_e);
    window.draw(back_sp);

    window.draw(name_ed);
    window.draw(age_ed);
    window.draw(health_ed);
    window.draw(breed_ed);
    window.draw(species_ed);
    if (name_selectEdit || age_selectEdit || health_selectEdit || species_selectEdit || breed_selectEdit) {
        window.draw(edit_box_id);
        window.draw(edit_box);
        window.draw(edit_id);
        window.draw(updateBOX);
        window.draw(UpdateBoxText);
    }
    if (name_selectEdit)
        window.draw(edit_name);

    if (age_selectEdit)
        window.draw(edit_age);

    if (breed_selectEdit)
        window.draw(edit_breed);

    if (species_selectEdit)
        window.draw(edit_species);

    if (health_selectEdit)
        window.draw(edit_health);

    window.draw(name_edit);
    window.draw(age_edit);
    window.draw(breed_edit);
    window.draw(species_edit);
    window.draw(health_edit);
    window.draw(id_edit);

}
void Updatepet() {
    makeUpdate();
    string input_id, input_name, input_age, input_health, input_breed, input_species;
    bool found = false;

    name_selectEdit = false;
    age_selectEdit = false;
    health_selectEdit = false;
    breed_selectEdit = false;
    species_selectEdit = false;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();


            if (event.type == Event::MouseButtonPressed) {
                Vector2i mousePos = Mouse::getPosition(window);
                if (name_e.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    name_selectEdit = true;
                    age_selectEdit = false;
                    health_selectEdit = false;
                    breed_selectEdit = false;
                    species_selectEdit = false;
                    input_id = "";
                    input_name = "";
                    input_age = "";
                    input_breed = "";
                    input_species = "";
                    input_health = "";
                    id_edit.setString(input_id);
                    name_edit.setString(input_name);
                    age_edit.setString(input_age);
                    health_edit.setString(input_health);
                    breed_edit.setString(input_breed);
                    species_edit.setString(input_species);

                }
                if (age_e.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    name_selectEdit = false;
                    age_selectEdit = true;
                    health_selectEdit = false;
                    breed_selectEdit = false;
                    species_selectEdit = false;
                    input_id = "";
                    input_name = "";
                    input_age = "";
                    input_breed = "";
                    input_species = "";
                    input_health = "";
                    id_edit.setString(input_id);
                    name_edit.setString(input_name);
                    age_edit.setString(input_age);
                    health_edit.setString(input_health);
                    breed_edit.setString(input_breed);
                    species_edit.setString(input_species);

                }
                if (health_e.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    name_selectEdit = false;
                    age_selectEdit = false;
                    health_selectEdit = true;
                    breed_selectEdit = false;
                    species_selectEdit = false;
                    input_id = "";
                    input_name = "";
                    input_age = "";
                    input_breed = "";
                    input_species = "";
                    input_health = "";
                    id_edit.setString(input_id);
                    name_edit.setString(input_name);
                    age_edit.setString(input_age);
                    health_edit.setString(input_health);
                    breed_edit.setString(input_breed);
                    species_edit.setString(input_species);
                }
                if (breed_e.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    name_selectEdit = false;
                    age_selectEdit = false;
                    health_selectEdit = false;
                    breed_selectEdit = true;
                    species_selectEdit = false;
                    input_id = "";
                    input_name = "";
                    input_age = "";
                    input_breed = "";
                    input_species = "";
                    input_health = "";
                    id_edit.setString(input_id);
                    name_edit.setString(input_name);
                    age_edit.setString(input_age);
                    health_edit.setString(input_health);
                    breed_edit.setString(input_breed);
                    species_edit.setString(input_species);

                }
                if (species_e.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    name_selectEdit = false;
                    age_selectEdit = false;
                    health_selectEdit = false;
                    breed_selectEdit = false;
                    species_selectEdit = true;
                    input_id = "";
                    input_name = "";
                    input_age = "";
                    input_breed = "";
                    input_species = "";
                    input_health = "";
                    id_edit.setString(input_id);
                    name_edit.setString(input_name);
                    age_edit.setString(input_age);
                    health_edit.setString(input_health);
                    breed_edit.setString(input_breed);
                    species_edit.setString(input_species);
                }

                if (edit_box_id.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    id_boxEdit = true;
                    other_box = false;
                }
                if (edit_box.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    other_box = true;
                    id_boxEdit = false;
                }
                if (updateBOX.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    found = false;
                    if (name_selectEdit) {
                        for (int i = 0;i < pets.size();i++) {
                            if (input_id == pets[i].id) {
                                found = true;
                                if (input_name == pets[i].name) {

                                    errorbox("this is already the name", 40, 50);
                                }
                                else {
                                    pets[i].name = input_name;
                                    added("pet name is updated", 45, 50);
                                    writePets(pets);
                                }
                            }
                        }
                        if (!found) {
                            errorbox("pet id is not valid !", 70, 50);
                        }
                        input_id = "";
                        input_name = "";
                        input_age = "";
                        input_breed = "";
                        input_species = "";
                        input_health = "";
                        id_edit.setString(input_id);
                        name_edit.setString(input_name);
                        age_edit.setString(input_age);
                        health_edit.setString(input_health);
                        breed_edit.setString(input_breed);
                        species_edit.setString(input_species);
                    }

                    else  if (age_selectEdit) {
                        for (int i = 0;i < pets.size();i++) {
                            if (input_id == pets[i].id) {
                                found = true;
                                if (input_age == pets[i].age) {

                                    errorbox("this is already the age", 42, 50);
                                }
                                else {
                                    pets[i].age = input_age;
                                    added("pet age is updated", 47, 50);
                                    writePets(pets);
                                }
                            }
                        }
                        if (!found) {
                            errorbox("pet id is not valid !", 70, 50);
                        }
                        input_id = "";
                        input_name = "";
                        input_age = "";
                        input_breed = "";
                        input_species = "";
                        input_health = "";
                        id_edit.setString(input_id);
                        name_edit.setString(input_name);
                        age_edit.setString(input_age);
                        health_edit.setString(input_health);
                        breed_edit.setString(input_breed);
                        species_edit.setString(input_species);
                    }

                    else  if (health_selectEdit) {
                        for (int i = 0;i < pets.size();i++) {
                            if (input_id == pets[i].id) {
                                found = true;
                                if (input_health == pets[i].health) {

                                    errorbox("this is already the health", 38, 50);
                                }
                                else {
                                    pets[i].health = input_health;
                                    added("pet health is updated", 42, 50);
                                    writePets(pets);
                                }
                            }
                        }
                        if (!found) {
                            errorbox("pet id is not valid !", 70, 50);
                        }
                        input_id = "";
                        input_name = "";
                        input_age = "";
                        input_breed = "";
                        input_species = "";
                        input_health = "";
                        id_edit.setString(input_id);
                        name_edit.setString(input_name);
                        age_edit.setString(input_age);
                        health_edit.setString(input_health);
                        breed_edit.setString(input_breed);
                        species_edit.setString(input_species);
                    }

                    else  if (breed_selectEdit) {
                        for (int i = 0;i < pets.size();i++) {
                            if (input_id == pets[i].id) {
                                found = true;
                                if (input_breed == pets[i].breed) {

                                    errorbox("this is already the breed", 38, 50);
                                }
                                else {
                                    pets[i].breed = input_breed;

                                    added("pet breed is updated", 42, 50);
                                    writePets(pets);
                                }
                            }
                        }
                        if (!found) {
                            errorbox("pet id is not valid !", 70, 50);
                        }
                        input_id = "";
                        input_name = "";
                        input_age = "";
                        input_breed = "";
                        input_species = "";
                        input_health = "";
                        id_edit.setString(input_id);
                        name_edit.setString(input_name);
                        age_edit.setString(input_age);
                        health_edit.setString(input_health);
                        breed_edit.setString(input_breed);
                        species_edit.setString(input_species);
                    }

                    else  if (species_selectEdit) {
                        for (int i = 0;i < pets.size();i++) {
                            if (input_id == pets[i].id) {
                                found = true;
                                if (input_species == pets[i].species) {

                                    errorbox("this is already the species", 30, 50);
                                }
                                else {
                                    pets[i].species = input_species;
                                    added("pet species is updated", 40, 50);
                                    writePets(pets);
                                }
                            }
                        }
                        if (!found) {
                            errorbox("pet id is not valid !", 70, 50);
                        }
                        input_id = "";
                        input_name = "";
                        input_age = "";
                        input_breed = "";
                        input_species = "";
                        input_health = "";
                        id_edit.setString(input_id);
                        name_edit.setString(input_name);
                        age_edit.setString(input_age);
                        health_edit.setString(input_health);
                        breed_edit.setString(input_breed);
                        species_edit.setString(input_species);
                    }





                }

                if (back_sp.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    // page_user();
                    adminpage();
                }


            }
            if (event.type == Event::TextEntered) {
                if (event.text.unicode < 128) {
                    char enteredChar = static_cast<char>(event.text.unicode);

                    if (id_boxEdit) {
                        if (enteredChar == 8 && !input_id.empty())
                            input_id.pop_back();
                        else if (isprint(enteredChar))
                            input_id += enteredChar;
                        id_edit.setString(input_id);
                    }
                    if (other_box && name_selectEdit) {
                        if (enteredChar == 8 && !input_name.empty())
                            input_name.pop_back();
                        else if (isprint(enteredChar))
                            input_name += enteredChar;
                        name_edit.setString(input_name);

                    }
                    if (other_box && age_selectEdit) {
                        if (enteredChar == 8 && !input_age.empty())
                            input_age.pop_back();
                        else if (isprint(enteredChar))
                            input_age += enteredChar;
                        age_edit.setString(input_age);

                    }
                    if (other_box && health_selectEdit) {
                        if (enteredChar == 8 && !input_health.empty())
                            input_health.pop_back();
                        else if (isprint(enteredChar))
                            input_health += enteredChar;
                        health_edit.setString(input_health);

                    }
                    if (other_box && breed_selectEdit) {
                        if (enteredChar == 8 && !input_breed.empty())
                            input_breed.pop_back();
                        else if (isprint(enteredChar))
                            input_breed += enteredChar;
                        breed_edit.setString(input_breed);

                    }
                    if (other_box && species_selectEdit) {
                        if (enteredChar == 8 && !input_species.empty())
                            input_species.pop_back();
                        else if (isprint(enteredChar))
                            input_species += enteredChar;
                        species_edit.setString(input_species);

                    }



                }
            }



        }

        window.clear();
        drawUpdate();
        window.display();
    }
} 

// Descision of requests page
void makeAdmindecision() {

    if (!back_tex.loadFromFile("back.png")) {
        cout << "Failed to load button\n";
    }

    back_sp.setTexture(back_tex);
    back_sp.setScale(0.35, 0.35);
    back_sp.setPosition(1200, 20);

    if (!tex_backgroundReq.loadFromFile("r.png")) {
        cout << "Failed to load background\n";
    }
    spr_backgroundReq.setTexture(tex_backgroundReq);


    if (!tex_rectangle1.loadFromFile("rectangle.png")) {
        cout << "Failed to load background\n";
    }
    admincard.spr_rectangle.setTexture(tex_rectangle1);
    admincard.spr_rectangle.setPosition(100, 300);

    if (!arrow_buttontex.loadFromFile("slides.png")) {
        cout << "Failed to load background\n";
    }
    arrow_buttonspr.setTexture(arrow_buttontex);
    arrow_buttonspr.setPosition(20, 500);
    arrow_buttonspr.setScale(0.5, 0.5);

    arrow_buttonspr2.setTexture(arrow_buttontex);
    arrow_buttonspr2.setPosition(535, 500);
    arrow_buttonspr2.setScale(-0.5, 0.5);

    if (!button_tex.loadFromFile("button.png")) {
        cout << "Failed to load button\n";
    }
    admincard.acceptButton_spr.setTexture(button_tex);
    admincard.acceptButton_spr.setPosition(155, 650);
    admincard.acceptButton_spr.setScale(0.5, 0.5);

    admincard.rejectButton_spr.setTexture(button_tex);
    admincard.rejectButton_spr.setPosition(155, 710);
    admincard.rejectButton_spr.setScale(0.5, 0.5);

    if (!backButtonTexture.loadFromFile("back.png")) {
        cout << "Error loading back.png\n";
    }
    backButton.setTexture(backButtonTexture);
    backButton.setPosition(10, 10);
    backButton.setScale(0.25f, 0.25f);

    if (!font.loadFromFile("spring-egg.regular.ttf")) {
        cout << "Failed to load font\n";
    }
    request.setFont(font);
    request.setString("  REQUESTS ");
    request.setCharacterSize(45);
    request.setPosition(475, 170);


    admincard.approve.setFont(font);
    admincard.approve.setString("approve");
    admincard.approve.setCharacterSize(20);
    admincard.approve.setPosition(220, 670);

    admincard.reject.setFont(font);
    admincard.reject.setString("reject");
    admincard.reject.setCharacterSize(20);
    admincard.reject.setPosition(220, 730);

    admincard.user_ID.setFont(font);
    admincard.user_ID.setString("user_ID:");
    admincard.user_ID.setCharacterSize(20);
    admincard.user_ID.setPosition(120, 350);
    admincard.user_ID.setFillColor(Color(70, 40, 10));

    admincard.pet_ID.setFont(font);
    admincard.pet_ID.setString("pet_ID:");
    admincard.pet_ID.setCharacterSize(20);
    admincard.pet_ID.setPosition(120, 410);
    admincard.pet_ID.setFillColor(Color(70, 40, 10));

    admincard.request_ID.setFont(font);
    admincard.request_ID.setString("request_ID:");
    admincard.request_ID.setCharacterSize(20);
    admincard.request_ID.setPosition(120, 470);
    admincard.request_ID.setFillColor(Color(70, 40, 10));

    admincard.score_req.setFont(font);
    admincard.score_req.setString("score:");
    admincard.score_req.setCharacterSize(20);
    admincard.score_req.setPosition(120, 530);
    admincard.score_req.setFillColor(Color(70, 40, 10));

    admincard.Date.setFont(font);
    admincard.Date.setString("Date:");
    admincard.Date.setCharacterSize(20);
    admincard.Date.setPosition(120, 600);
    admincard.Date.setFillColor(Color(70, 40, 10));

    admincard.cuser_ID.setFont(font);
    admincard.cuser_ID.setCharacterSize(17);
    admincard.cuser_ID.setPosition(225, 350);
   

    admincard.cpet_ID.setFont(font);
    admincard.cpet_ID.setCharacterSize(17);
    admincard.cpet_ID.setPosition(210, 410);
 

    admincard.crequest_ID.setFont(font);
    admincard.crequest_ID.setCharacterSize(17);
    admincard.crequest_ID.setPosition(275, 470);
 

    admincard.cscore_req.setFont(font);
    admincard.cscore_req.setCharacterSize(17);
    admincard.cscore_req.setPosition(210, 530);


    admincard.cDate.setFont(font);
    admincard.cDate.setCharacterSize(17);
    admincard.cDate.setPosition(210, 600);

}
void drawAdmindecision(RenderWindow& window) {
    window.draw(spr_backgroundReq);
    window.draw(request);

    if (appear) {
    
        window.draw(admincard.spr_rectangle);
        window.draw(arrow_buttonspr);
        window.draw(arrow_buttonspr2);
        window.draw(admincard.acceptButton_spr);
        window.draw(admincard.rejectButton_spr);
        window.draw(admincard.approve);
        window.draw(admincard.reject);
        window.draw(admincard.user_ID);
        window.draw(admincard.pet_ID);
        window.draw(admincard.request_ID);
        window.draw(admincard.score_req);
        window.draw(admincard.Date);
        window.draw(admincard.cuser_ID);
        window.draw(admincard.cpet_ID);
        window.draw(admincard.crequest_ID);
        window.draw(admincard.cscore_req);
        window.draw(admincard.cDate);
    }
    window.draw(back_sp);
}
void Admindecisionpage() {
    thisnotification admin_not;
    Mouse ms;
    vector<AdoptionRequest*> pendingRequests;
    int currentindex = 0;
    bool buttonClicked = false;
    appear = true;

    for (int i = adoptionRequests.size() - 1; i >= 0; i--) {
        if (adoptionRequests[i].status == "pending") {
            pendingRequests.push_back(&adoptionRequests[i]);
        }
    }
    if (adoptionRequests.empty()) {
        errorbox("there is no requests", 45, 50);
        adminpage();

    }
    makeAdmindecision();

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

                if (!pendingRequests.empty() && !buttonClicked) {

                    if (admincard.acceptButton_spr.getGlobalBounds().contains(mousePos)) {

                        pendingRequests[currentindex]->status = "approved";
                      //  saveAllData();
                        added("     pet's request \n     is approved", 45, 30);
                        for (auto& pet : pets) {
                            if (pet.id == pendingRequests[currentindex]->pet_id) {
                                pet.availability = "unavailable";
                                admin_not.decision = true;
                                admin_not.pet_id = pet.id;
                                admin_not.user_id = pendingRequests[currentindex]->user_id;
                                not_vector.push_back(admin_not);
                                writeNotification(not_vector);
                                writePets(pets);
                                writeAdoptionRequests(adoptionRequests);
                                cout << "pet is approved " << endl;
                                break;
                            }
                        }



                        pendingRequests.erase(pendingRequests.begin() + currentindex);

                        if (currentindex >= pendingRequests.size() && !pendingRequests.empty()) {
                            currentindex = pendingRequests.size() - 1;
                        }
                        else if (pendingRequests.empty()) {
                            appear = true;
                            currentindex = 0;
                        }

                        buttonClicked = true;
                    }

                    else if (admincard.rejectButton_spr.getGlobalBounds().contains(mousePos)) {

                        pendingRequests[currentindex]->status = "rejected";
                        added("pet's request is rejected", 12, 50);
                       // saveAllData();
                        for (auto& pet : pets) {
                            if (pet.id == pendingRequests[currentindex]->pet_id) {
                                admin_not.decision = false;
                                admin_not.pet_id = pet.id;
                                admin_not.user_id = pendingRequests[currentindex]->user_id;
                                not_vector.push_back(admin_not);
                                writeNotification(not_vector);
                                writeAdoptionRequests(adoptionRequests);
                                cout << "pet is rejected " << endl;
                                break;
                            }
                        }

                        pendingRequests.erase(pendingRequests.begin() + currentindex);

                        if (currentindex >= pendingRequests.size() && !pendingRequests.empty()) {
                            currentindex = pendingRequests.size() - 1;
                        }
                        else if (pendingRequests.empty()) {
                            appear = false;
                            currentindex = 0;
                        }

                        buttonClicked = true;
                    }
                }

                if (!buttonClicked && arrow_buttonspr.getGlobalBounds().contains(mousePos)) {
                    if (currentindex < pendingRequests.size() - 1) {
                        currentindex++;
                    }
                }
                if (!buttonClicked && arrow_buttonspr2.getGlobalBounds().contains(mousePos)) {
                    if (currentindex > 0) {
                        currentindex--;
                    }
                }


                if (back_sp.getGlobalBounds().contains(mousePos)) {
                   adminpage();
                   // page_user();
                    return;
                }
            }

            if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
                buttonClicked = false;
            }
        }

        if (!pendingRequests.empty() && currentindex < pendingRequests.size()) {
            admincard.crequest_ID.setString(pendingRequests[currentindex]->request_id);
            admincard.cuser_ID.setString(pendingRequests[currentindex]->user_id);
            admincard.cpet_ID.setString(pendingRequests[currentindex]->pet_id);
            admincard.cscore_req.setString(to_string(pendingRequests[currentindex]->score));
            admincard.cDate.setString(pendingRequests[currentindex]->date);
            appear = true;
        }
        else {
            appear = false;
        }

        window.clear();
        drawAdmindecision(window);
        window.display();
    }
}
void centerTextInBox1(Text& text, const Sprite& box) {
    FloatRect textBounds = text.getLocalBounds();
    FloatRect boxBounds = box.getGlobalBounds();

    float x = boxBounds.left + (boxBounds.width - textBounds.width) / 2 - textBounds.left;
    float y = boxBounds.top + (boxBounds.height - textBounds.height) / 2 - textBounds.top;

    text.setPosition(x, y);
}

// Remove pet page
void runRemoveScreen() {
    Font font;
    bool r = false;

    font.loadFromFile("spring-egg.regular.ttf");


    if (!back_tex.loadFromFile("back.png")) {
        cout << "Failed to load button\n";
    }

    back_sp.setTexture(back_tex);
    back_sp.setScale(0.35, 0.35);
    back_sp.setPosition(1200, 20);


    Texture bgTexture, boxTexture, buttonTexture;
    bgTexture.loadFromFile("back_remove.png");
    boxTexture.loadFromFile("filled_box.png");
    buttonTexture.loadFromFile("button.png");

    Sprite background(bgTexture);
    Sprite inputBox(boxTexture);
    inputBox.setPosition(400, 350);

    Sprite removeButton(buttonTexture);
    removeButton.setScale(0.75f, 0.75f);
    removeButton.setPosition(480, 500);


    Text idLabel("ID", font, 40);
    idLabel.setFillColor(Color(90, 50, 30));
    idLabel.setPosition(340, 383);

    string idInput = "";
    Text idText("", font, 28);
    idText.setFillColor(Color::Black);

    Text removeButtonText("Remove", font, 30);
    FloatRect btnBounds = removeButtonText.getLocalBounds();
    removeButtonText.setOrigin(btnBounds.width / 2, btnBounds.height / 2);
    removeButtonText.setPosition(
        removeButton.getPosition().x + removeButton.getGlobalBounds().width / 2,
        removeButton.getPosition().y + removeButton.getGlobalBounds().height / 2
    );

    Text messageText("", font, 24);
    bool showMessage = false;
    Color messageColor = Color::Red;
    string messageContent = "";

    Text titleText("removing pet", font, 45);
    titleText.setFillColor(Color(70, 30, 20));
    titleText.setPosition(465, 255);
    titleText.setStyle(Text::Bold);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            else if (event.type == Event::MouseButtonPressed) {

                sf::Vector2f mouse(event.mouseButton.x, event.mouseButton.y);

                if (removeButton.getGlobalBounds().contains(mouse)) {
                    if (idInput.empty()) {

                        errorbox("Please enter an ID", 70, 50);
                    }
                    else {
                        for (int i = 0;i < pets.size();i++) {
                            if (pets[i].id == idInput) {
                                r = true;
                             //  for (int j = i + 1;j < pets.size();j++) {
                               //     pets[j].id = "petia_" + to_string(j);
                               // }

                                pets.erase(pets.begin() + i);
                                writePets(pets);

                                added("Removed successfully!", 30, 50);
                                idInput.clear();
                                idText.setString("");


                            }
                        }

                        if (!r) {
                            errorbox("INVALID ID !", 125, 50);
                        }


                    }
                }

                ////hereee
                if (back_sp.getGlobalBounds().contains(mouse)) {
                    idInput.clear();
                    idText.setString("");
                    adminpage();
                    // page_user();
                }
            }

            else if (event.type == Event::TextEntered) {
                if (event.text.unicode == 8 && !idInput.empty()) {
                    idInput.pop_back();
                }
                else if (event.text.unicode >= 32 && event.text.unicode <= 126) {
                    idInput += static_cast<char>(event.text.unicode);
                }
                idText.setString(idInput);
            }
        }

        FloatRect boxBounds = inputBox.getGlobalBounds();
        FloatRect textBounds = idText.getLocalBounds();
        idText.setOrigin(textBounds.width / 2, textBounds.height / 2);
        idText.setPosition(
            boxBounds.left + boxBounds.width / 2,
            boxBounds.top + boxBounds.height / 2 + 5
        );

        messageText.setString(messageContent);
        messageText.setFillColor(messageColor);
        messageText.setPosition(boxBounds.left + 20, boxBounds.top + boxBounds.height + 20);

        window.clear();
        window.draw(background);
        window.draw(titleText);
        window.draw(idLabel);
        window.draw(inputBox);
        window.draw(idText);
        window.draw(removeButton);
        window.draw(removeButtonText);
        // window.draw(backButton);
        window.draw(back_sp);
        window.display();
    }
}

// First admin page
void makeadminpage() {
    if (!back_tex.loadFromFile("back.png")) {
        cout << "Failed to load button\n";
    }

    back_sp.setTexture(back_tex);
    back_sp.setScale(0.35, 0.35);
    back_sp.setPosition(1200, 20);

    if (!tex_backgroundReq.loadFromFile("back_admin1.png")) {
        cout << "Failed to load background\n";
    }
    spr_backgroundReq.setTexture(tex_backgroundReq);

   
    if (!tex_rectangle1.loadFromFile("rectangle.png")) {
        cout << "Failed to load background\n";
    }
    admincard.spr_rectangle.setTexture(tex_rectangle1);
    admincard.spr_rectangle.setPosition(100, 300);

    if (!button_tex.loadFromFile("button.png")) {
        cout << "Failed to load button\n";
    }

    padmin.decisionbutton.setTexture(button_tex);
    padmin.decisionbutton.setPosition(155, 350);
    padmin.decisionbutton.setScale(0.5, 0.5);

    padmin.addbutton.setTexture(button_tex);
    padmin.addbutton.setPosition(155, 450);
    padmin.addbutton.setScale(0.5, 0.5);

    padmin.removebutton.setTexture(button_tex);
    padmin.removebutton.setPosition(155, 550);
    padmin.removebutton.setScale(0.5, 0.5);

    padmin.editbutton.setTexture(button_tex);
    padmin.editbutton.setPosition(155, 650);
    padmin.editbutton.setScale(0.5, 0.5);

    if (!font.loadFromFile("spring-egg.regular.ttf")) {
        cout << "Failed to load font\n";
    }
    request.setFont(font);
    request.setString("-Admin Page-");
    request.setCharacterSize(45);
    request.setPosition(475, 170);

    padmin.decision.setFont(font);
    padmin.decision.setString("make_decision");
    padmin.decision.setCharacterSize(20);
    padmin.decision.setPosition(185, 365);

    padmin.add.setFont(font);
    padmin.add.setString("Add");
    padmin.add.setCharacterSize(20);
    padmin.add.setPosition(245, 468);

    padmin.remove.setFont(font);
    padmin.remove.setString("Remove");
    padmin.remove.setCharacterSize(20);
    padmin.remove.setPosition(225, 568);

    padmin.edit.setFont(font);
    padmin.edit.setString("Edit");
    padmin.edit.setCharacterSize(20);
    padmin.edit.setPosition(245, 668);


}
void drawadminpage() {
    window.draw(spr_backgroundReq);
    window.draw(request);
  
    window.draw(admincard.spr_rectangle);
    window.draw(padmin.decisionbutton);
    window.draw(padmin.addbutton);
    window.draw(padmin.removebutton);
    window.draw(padmin.editbutton);
    window.draw(padmin.decision);
    window.draw(padmin.add);
    window.draw(padmin.remove);
    window.draw(padmin.edit);
    window.draw(back_sp);
}
void adminpage() {
    //padmin.decisionbutton    padmin.addbutton   padmin.removebutton  padmin.editbutton
    makeadminpage();

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();


            if (event.type == Event::MouseButtonPressed) {
                Vector2i mousePos = Mouse::getPosition(window);
                if (padmin.decisionbutton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    Admindecisionpage();
                }
                if (padmin.addbutton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    addadmin();
                }
                if (padmin.removebutton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    runRemoveScreen();
                }
                if (padmin.editbutton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    Updatepet();
                }
                if (back_sp.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    firstpage();
                 //   page_user();
                }

            }
        }
        window.clear();

        drawadminpage();

        window.display();
    }
}


// ==============================================
// User Functions 
// ==============================================

// Assesment pages
string getCurrentDate() {
    time_t now = time(0);  //stores the current system time as the number of seconds since January 1, 1970
    struct tm ltm;
    localtime_s(&ltm, &now);  //converts now into a tm struct (ltm) containing year, month, day
    return to_string(1900 + ltm.tm_year) + "-" +    //start counting from 1900
        to_string(1 + ltm.tm_mon) + "-" +           //works from 0 to 11
        to_string(ltm.tm_mday);                     //from 1 to 31
}
void makeStartPage() {
    if (!ansbutton.loadFromFile("button.png")) {
        cout << "Failed to load button texture\n";
    }

    // Load box background
    if (!assessFinishedback.loadFromFile("assessfinishback.png")) {
        cout << "Failed to load start page background\n";
        assessFinishedback.create(400, 400);
    }
    sprfinish.setTexture(assessFinishedback);
    sprfinish.setPosition(150, 300);
    sprfinish.setScale(1, 0.8);

    // create OK button
    startOkButton.setTexture(ansbutton);
    startOkButton.setPosition(480, 630);
    startOkButton.setScale(0.6, 0.6);

    // create Close button
    if (!closetex.loadFromFile("close button.png")) {
        cout << "Failed to load start page background\n";
    }
    startCloseButton.setTexture(closetex);
    startCloseButton.setPosition(1020, 308);
    startCloseButton.setScale(0.2, 0.2);

    // create start page text
    startText.setFont(font);
    startText.setString("This is a small assessment to help us \n determine if your "
        "home environment\n and lifestyle are "
        "appropriate for\n pet ownership.");
    startText.setCharacterSize(30);
    startText.setPosition(270, 380);

    // create ok button text
    okButtonText.setFont(font);
    okButtonText.setString("OK");
    okButtonText.setCharacterSize(30);
    okButtonText.setPosition(600, 650);
}
void makequiz1() {
    if (!quizbackground_tex.loadFromFile("back_ques (1).png")) {
        cout << "Failed to load background\n";
    }
    quizbackground_spr.setTexture(quizbackground_tex);

    if (!ansbutton.loadFromFile("button.png")) {
        cout << "Failed to load button\n";
    }

    ans11.setTexture(ansbutton);
    ans12.setTexture(ansbutton);
    ans11.setPosition(200, 370);
    ans12.setPosition(740, 370);
    ans11.setScale(0.8, 0.8);
    ans12.setScale(0.8, 0.8);

    q1.setFont(font);
    q1.setString("Have you owned a pet before?");
    q1.setCharacterSize(45);
    q1.setPosition(230, 290);

    q1a.setFont(font);
    q1a.setString("yes");
    q1a.setCharacterSize(45);
    q1a.setPosition(325, 395);

    q1b.setFont(font);
    q1b.setString("no");
    q1b.setCharacterSize(45);
    q1b.setPosition(900, 395);

    ans21.setTexture(ansbutton);
    ans22.setTexture(ansbutton);
    ans21.setPosition(200, 640);
    ans22.setPosition(740, 640);
    ans21.setScale(0.8, 0.8);
    ans22.setScale(0.8, 0.8);

    q2.setFont(font);
    q2.setString("Do you want a pet as a lifelong companion?");
    q2.setCharacterSize(39);
    q2.setPosition(120, 560);

    q2a.setFont(font);
    q2a.setString("yes");
    q2a.setCharacterSize(45);
    q2a.setPosition(325, 660);

    q2b.setFont(font);
    q2b.setString("no");
    q2b.setCharacterSize(45);
    q2b.setPosition(900, 660);

    ans11.setColor(defaultColor);
    ans12.setColor(defaultColor);
    ans21.setColor(defaultColor);
    ans22.setColor(defaultColor);
}
void drawquiz1() {
    window.draw(quizbackground_spr);
    window.draw(ans11);
    window.draw(ans12);
    window.draw(q1);
    window.draw(q1a);
    window.draw(q1b);
    window.draw(ans21);
    window.draw(ans22);
    window.draw(q2);
    window.draw(q2a);
    window.draw(q2b);
}
void makequiz2() {
    if (!quizbackground_tex.loadFromFile("back_ques (1).png")) {
        cout << "Failed to load background\n";
    }
    quizbackground_spr.setTexture(quizbackground_tex);

    if (!ansbutton.loadFromFile("button.png")) {
        cout << "Failed to load button\n";
    }

    ans31.setTexture(ansbutton);
    ans32.setTexture(ansbutton);
    ans31.setPosition(200, 370);
    ans32.setPosition(740, 370);
    ans31.setScale(0.8, 0.8);
    ans32.setScale(0.8, 0.8);

    q3.setFont(font);
    q3.setString("Do you currently have any pets?");
    q3.setCharacterSize(45);
    q3.setPosition(200, 290);

    q3a.setFont(font);
    q3a.setString("yes");
    q3a.setCharacterSize(45);
    q3a.setPosition(325, 395);

    q3b.setFont(font);
    q3b.setString("no");
    q3b.setCharacterSize(45);
    q3b.setPosition(900, 395);

    ans41.setTexture(ansbutton);
    ans42.setTexture(ansbutton);
    ans41.setPosition(200, 640);
    ans42.setPosition(740, 640);
    ans41.setScale(0.8, 0.8);
    ans42.setScale(0.8, 0.8);

    q4.setFont(font);
    q4.setString("Will the pet be allowed to stay inside the house?");
    q4.setCharacterSize(33);
    q4.setPosition(120, 560);

    q4a.setFont(font);
    q4a.setString("yes");
    q4a.setCharacterSize(45);
    q4a.setPosition(325, 660);

    q4b.setFont(font);
    q4b.setString("no");
    q4b.setCharacterSize(45);
    q4b.setPosition(900, 660);

    ans31.setColor(defaultColor);
    ans32.setColor(defaultColor);
    ans41.setColor(defaultColor);
    ans42.setColor(defaultColor);
}
void drawquiz2() {
    window.draw(quizbackground_spr);
    window.draw(ans31);
    window.draw(ans32);
    window.draw(q3);
    window.draw(q3a);
    window.draw(q3b);
    window.draw(ans41);
    window.draw(ans42);
    window.draw(q4);
    window.draw(q4a);
    window.draw(q4b);
}
void makefinishedpage() {
    // Load box background texture
    if (!assessFinishedback.loadFromFile("assessfinishback.png")) {
        cout << "Failed to load popup background\n";
        assessFinishedback.create(280, 280);
    }
    sprfinish.setTexture(assessFinishedback);
    sprfinish.setPosition(150, 300);
    sprfinish.setScale(1, 0.53);

    // create OK button
    okButton.setTexture(ansbutton);
    okButton.setPosition(480, 470);
    okButton.setScale(0.6, 0.6);

    // create OK button text
    okButtonText.setFont(font);
    okButtonText.setString("OK");
    okButtonText.setCharacterSize(30);
    okButtonText.setPosition(600, 490);


    // create thank you text
    thankYouText.setFont(font);
    thankYouText.setString("Thank you! Your request is pending.");
    thankYouText.setCharacterSize(30);
    thankYouText.setPosition(270, 380);
    thankYouText.setCharacterSize(35);


    showfinishedpage = true;
}
int runAdoptionQuiz(const string& petId) {
    selectedPetId = petId;  // Store which pet this assessment is for
    int score = 0;

    showfinishedpage = false;
    showStartPage = true;
    assessmentStarted = false;

    bool quiz1Complete = false;
    bool quiz2Complete = false;
    char answers[4] = { ' ', ' ', ' ', ' ' };

    makequiz1();
    makequiz2();
    makeStartPage();

    while (window.isOpen()) {
        window.clear();
        drawUser();
        window.draw(text_search);

        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::MouseButtonReleased) {
                Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));

                if (showStartPage) {
                    if (startOkButton.getGlobalBounds().contains(mousePos)) {
                        showStartPage = false;
                        assessmentStarted = true;
                    }
                    else if (startCloseButton.getGlobalBounds().contains(mousePos)) {
                        return -1; // Return -1 to indicate assessment was cancelled
                    }
                }
                else if (showfinishedpage) {
                    if (okButton.getGlobalBounds().contains(mousePos)) {
                        // Create and store the adoption request
                        AdoptionRequest newRequest;
                        newRequest.request_id = "request_" + to_string(requestCounter++);
                        newRequest.user_id = userid_adoption;   // Empty as requested
                        newRequest.pet_id = selectedPetId;
                        newRequest.status = "pending";
                        newRequest.date = getCurrentDate();
                        newRequest.score = score;

                        adoptionRequests.push_back(newRequest);

                        cout << "Request created: " << newRequest.request_id
                            << " for pet: " << newRequest.pet_id
                            << " with score: " << newRequest.score << endl;

                        return score;
                    }
                }
                else if (assessmentStarted && !quiz1Complete) {
                    if (ans11.getGlobalBounds().contains(mousePos)) {
                        answers[0] = 'a';
                        // No color change - button stays default color
                    }
                    else if (ans12.getGlobalBounds().contains(mousePos)) {
                        answers[0] = 'b';
                        // No color change - button stays default color
                    }
                    else if (ans21.getGlobalBounds().contains(mousePos)) {
                        answers[1] = 'a';
                        // No color change - button stays default color
                    }
                    else if (ans22.getGlobalBounds().contains(mousePos)) {
                        answers[1] = 'b';
                        // No color change - button stays default color
                    }

                    if (answers[0] != ' ' && answers[1] != ' ') {
                        quiz1Complete = true;
                    }
                }
                else if (assessmentStarted && !quiz2Complete) {
                    if (ans31.getGlobalBounds().contains(mousePos)) {
                        answers[2] = 'a';
                        // No color change - button stays default color
                    }
                    else if (ans32.getGlobalBounds().contains(mousePos)) {
                        answers[2] = 'b';
                        // No color change - button stays default color
                    }
                    else if (ans41.getGlobalBounds().contains(mousePos)) {
                        answers[3] = 'a';
                        // No color change - button stays default color
                    }
                    else if (ans42.getGlobalBounds().contains(mousePos)) {
                        answers[3] = 'b';
                        // No color change - button stays default color
                    }

                    if (answers[2] != ' ' && answers[3] != ' ') {
                        quiz2Complete = true;
                        // Calculate score
                        for (int i = 0; i < 4; i++) {
                            if (answers[i] == 'a') score += 3;
                            else if (answers[i] == 'b') score += 1;
                        }
                        makefinishedpage();
                    }
                }
            }
        }

        if (showStartPage) {
            window.draw(sprfinish);
            window.draw(startOkButton);
            window.draw(startCloseButton);
            window.draw(startText);
            window.draw(okButtonText);
        }
        else if (assessmentStarted) {
            if (!quiz1Complete) {
                drawquiz1();
            }
            else if (!quiz2Complete) {
                drawquiz2();
            }
            else if (showfinishedpage) {
                window.draw(sprfinish);
                window.draw(okButton);
                window.draw(okButtonText);
                window.draw(thankYouText);
            }
        }

        window.display();
    }
    return score;
}
bool hasPendingRequest(const string& petId) {
    for (const auto& request : adoptionRequests) {
        if (request.pet_id == petId && request.status == "pending") {
            return true;
        }
    }
    return false;
}

// Notification page
void showNotificationsScreen() {
    bool found = false;

    if (!arrow_buttontex.loadFromFile("slide_not.png")) {
        cout << "Failed to load background\n";
    }
    Sprite slide_up, slide_down;

    slide_up.setTexture(arrow_buttontex);
    slide_up.setPosition(635, 180);
    slide_up.setScale(0.2, 0.2);


    slide_down.setTexture(arrow_buttontex);
    slide_down.setPosition(700, 877);
    slide_down.setScale(-0.2, -0.2);

    rectangle.loadFromFile("rec_not1.png");
     font.loadFromFile("spring-egg.regular.ttf");



    Texture backgroundTexture;
    backgroundTexture.loadFromFile("update_background.png");
    Sprite background;
    background.setTexture(backgroundTexture);

    if (!back_tex.loadFromFile("back.png")) {
        cout << "Failed to load button\n";
    }

    back_sp.setTexture(back_tex);
    back_sp.setScale(0.35, 0.35);
    back_sp.setPosition(1200, 20);

    Text title;
    title.setFont(font);
    title.setStyle(Text::Bold);
    title.setString("NOTIFICATIONS");
    title.setCharacterSize(32);
    setTextColorWhite(title);
    title.setPosition(530, 140);

    if (!remove_fav_tex.loadFromFile("x_fav.png")) {
        cout << "Failed to load background\n";
    }

    Texture below_not_tex;
    below_not_tex.loadFromFile("rec_not1.png");

   
    scrollOffset_notif = 0.0f;

    
    if (not_vector.empty()|| cnt_notification==0) {
        errorbox("there is no notifications", 40, 50);
        page_user();
    }
    while (window.isOpen()) {
       
       int x = 80, y = 245;
      //  int x = 80;
        
        for (int i = 0;i < not_vector.size();i++) {
            if (not_vector[i].decision) {
                not_vector[i].notification = "your request for " + not_vector[i].pet_id + " is approved =)";
            }
            else {
                not_vector[i].notification = "your request for " + not_vector[i].pet_id + " is rejected =(";
            }

            not_vector[i].below.setTexture(below_not_tex);
            not_vector[i].below.setPosition(x + 20, scrollOffset_notif + y);
            not_vector[i].below.setScale(0.97, 0.6);
            not_vector[i].notification_text.setFont(font);
            not_vector[i].notification_text.setString(not_vector[i].notification);
            not_vector[i].notification_text.setCharacterSize(32);
            not_vector[i].notification_text.setPosition(x + 135, scrollOffset_notif + y + 30);
            not_vector[i].x_not.setTexture(remove_fav_tex);
            not_vector[i].x_not.setScale(0.2, 0.2);
            not_vector[i].x_not.setPosition(1160, y + scrollOffset_notif+20);

                y += 120;


        }

        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Down) scrollOffset_notif -= 30;
                if (event.key.code == Keyboard::Up) scrollOffset_notif += 30;
            }
            Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
            if (back_sp.getGlobalBounds().contains(mousePos) && Mouse::isButtonPressed(Mouse::Left)) {
                page_user();
            }
            if (slide_up.getGlobalBounds().contains(mousePos) && Mouse::isButtonPressed(Mouse::Left)) {
              scrollOffset_notif -= 90;
              
              
            }

            if (slide_down.getGlobalBounds().contains(mousePos) && Mouse::isButtonPressed(Mouse::Left)) {
              scrollOffset_notif += 90;
         

            }

            for (int i = 0;i < not_vector.size();i++) {
                if (not_vector[i].x_not.getGlobalBounds().contains(mousePos) && Mouse::isButtonPressed(Mouse::Left)) {
               
                    not_vector.erase(not_vector.begin() + i);
                    cnt_notification--;
                 //   cout << "the notification decreased to" << cnt_notification << endl;
                    writeNotification(not_vector);
        
                }
            }
        }

        window.clear();
        window.draw(background);
        window.draw(back_sp);
       // window.draw(title);
        window.draw(slide_up);
        window.draw(slide_down);
        for (int i = 0;i < not_vector.size();i++) {
            if (not_vector[i].user_id == userid_adoption) {

                window.draw(not_vector[i].below);
                window.draw(not_vector[i].notification_text);
                window.draw(not_vector[i].x_not);

            }
       }
   
        window.display();
    }
}

// View requests page
void makeviewrequest() {

    if (!back_tex.loadFromFile("back.png")) {
        cout << "Failed to load button\n";
    }

    back_sp.setTexture(back_tex);
    back_sp.setScale(0.35, 0.35);
    back_sp.setPosition(1200, 20);

    if (!tex_backgroundReq.loadFromFile("back_requests2.png")) {
        cout << "Failed to load background\n";
    }
    spr_backgroundReq.setTexture(tex_backgroundReq);


    if (!tex_rectangle1.loadFromFile("rectangle.png")) {
        cout << "Failed to load background\n";
    }
    usercard.spr_rectangle.setTexture(tex_rectangle1);
    usercard.spr_rectangle.setPosition(100, 300);

    if (!arrow_buttontex.loadFromFile("slides.png")) {
        cout << "Failed to load background\n";
    }
    arrow_buttonspr.setTexture(arrow_buttontex);
    arrow_buttonspr.setPosition(20, 500);
    arrow_buttonspr.setScale(0.5, 0.5);

    arrow_buttonspr2.setTexture(arrow_buttontex);
    arrow_buttonspr2.setPosition(535, 500);
    arrow_buttonspr2.setScale(-0.5, 0.5);

    if (!font.loadFromFile("spring-egg.regular.ttf")) {
        cout << "Failed to load font\n";
    }
    request.setFont(font);
    request.setString("   REQUESTS ");
    request.setCharacterSize(45);
    request.setPosition(475, 170);


    usercard.pet_ID.setFont(font);
    usercard.pet_ID.setString("pet_ID:");
    usercard.pet_ID.setCharacterSize(20);
    usercard.pet_ID.setPosition(120, 340);
    usercard.pet_ID.setFillColor(Color(70, 40, 10));
  //  Color(70, 40, 10)

    usercard.request_ID.setFont(font);
    usercard.request_ID.setString("request_ID:");
    usercard.request_ID.setCharacterSize(20);
    usercard.request_ID.setPosition(120, 440);
    usercard.request_ID.setFillColor(Color(70, 40, 10));

    usercard.status.setFont(font);
    usercard.status.setString("status:");
    usercard.status.setCharacterSize(20);
    usercard.status.setPosition(120, 540);
    usercard.status.setFillColor(Color(70, 40, 10));

    usercard.Date.setFont(font);
    usercard.Date.setString("Date:");
    usercard.Date.setCharacterSize(20);
    usercard.Date.setPosition(120, 640);
    usercard.Date.setFillColor(Color(70, 40, 10));

    usercard.score_req.setFont(font);
    usercard.score_req.setString("score:");
    usercard.score_req.setCharacterSize(20);
    usercard.score_req.setPosition(120, 740);
    usercard.score_req.setFillColor(Color(70, 40, 10));

    usercard.cpet_ID.setFont(font);
    usercard.cpet_ID.setCharacterSize(17);
    usercard.cpet_ID.setPosition(210, 340);


    usercard.crequest_ID.setFont(font);
    usercard.crequest_ID.setCharacterSize(17);
    usercard.crequest_ID.setPosition(275, 440);


    usercard.cstatus.setFont(font);
    usercard.cstatus.setCharacterSize(17);
    usercard.cstatus.setPosition(220, 540);
  

    usercard.cDate.setFont(font);
    usercard.cDate.setCharacterSize(17);
    usercard.cDate.setPosition(210, 640);
  

    usercard.cscore_req.setFont(font);
    usercard.cscore_req.setCharacterSize(17);
    usercard.cscore_req.setPosition(210, 740);
  
}
void drawviewrequest(RenderWindow& window) {

    window.draw(spr_backgroundReq);
    window.draw(request);
   // window.draw(catpet_spr);
    //window.draw(dogpet_spr);
    window.draw(usercard.spr_rectangle);
    window.draw(arrow_buttonspr);
    window.draw(arrow_buttonspr2);
    window.draw(usercard.pet_ID);
    window.draw(usercard.request_ID);
    window.draw(usercard.status);
    window.draw(usercard.Date);
    window.draw(usercard.score_req);
    window.draw(usercard.cpet_ID);
    window.draw(usercard.crequest_ID);
    window.draw(usercard.cstatus);
    window.draw(usercard.cDate);
    window.draw(usercard.cscore_req);
    window.draw(back_sp);
}
void viewrequestpage() {
    vector<AdoptionRequest*> userRequests;
    int currentindex = 0;

    for (int i = 0; i < adoptionRequests.size(); i++) {
        if (adoptionRequests[i].user_id == userid_adoption) {
            userRequests.push_back(&adoptionRequests[i]);
        }

    }

    makeviewrequest();

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                Vector2f mousereq(event.mouseButton.x, event.mouseButton.y);

                // Left arrow - scroll to previous request
                if (arrow_buttonspr.getGlobalBounds().contains(mousereq)) {
                    if (currentindex > 0) {
                        currentindex--;
                        cout << "Scrolled to request " << (currentindex + 1) << endl;
                    }
                }

                // Right arrow - scroll to next request
                if (arrow_buttonspr2.getGlobalBounds().contains(mousereq)) {
                    if (currentindex < userRequests.size() - 1) {
                        currentindex++;
                        cout << "Scrolled to request " << (currentindex + 1) << endl;
                    }
                }
                if (back_sp.getGlobalBounds().contains(mousereq)) {
                    // adminpage();
                    page_user();
                }

            }


            // Update display with current request information
            if (!userRequests.empty() && currentindex < userRequests.size()) {
                usercard.cpet_ID.setString(userRequests[currentindex]->pet_id);
                usercard.crequest_ID.setString(userRequests[currentindex]->request_id);
                usercard.cstatus.setString(userRequests[currentindex]->status);
                usercard.cDate.setString(userRequests[currentindex]->date);
                usercard.cscore_req.setString(to_string(userRequests[currentindex]->score) + "/12");
            }
            else {
                errorbox("you have no requests ", 60, 50);
                page_user();
              
            }

            window.clear();
            drawviewrequest(window);
            window.display();
        }
    }
}

// Favourites page
void make_fav() {
    if (!tex_slide_s.loadFromFile("slides.png")) {
        cout << "Failed to load background\n";
    }
    if (!font.loadFromFile("spring-egg.regular.ttf")) {
        cout << "Failed to load font\n";
    }
    if (!back_fav_tex.loadFromFile("back_fav.png")) {
        cout << "Failed to load background\n";
    }

    if (!tex_box.loadFromFile("button.png")) {
        cout << "Failed to load background\n";
    }

    if (!under_tex.loadFromFile("under_fav.png")) {
        cout << "Failed to load background\n";
    }

    if (!remove_fav_tex.loadFromFile("x_fav.png")) {
        cout << "Failed to load background\n";
    }


    if (!back_tex.loadFromFile("back.png")) {
        cout << "Failed to load button\n";
    }

    back_sp.setTexture(back_tex);
    back_sp.setScale(0.35, 0.35);
    back_sp.setPosition(1200, 20);

    back_fav.setTexture(back_fav_tex);

    title_fav.setFont(font);
    title_fav.setString("your favourites");
    title_fav.setCharacterSize(44);
    title_fav.setFillColor(Color(70, 40, 10));
    title_fav.setStyle(Text::Bold);
    title_fav.setPosition(445, 180);

    slide_sRight.setTexture(tex_slide_s);
    slide_sRight.setScale(-0.3, 0.3);
    slide_sRight.setPosition(1290, 480);

    slide_sLeft.setTexture(tex_slide_s);
    slide_sLeft.setScale(0.3, 0.3);
    slide_sLeft.setPosition(10, 480);




    int x = 90, y = 305;
    int x_below = 75, y_below = 250;
    for (int i = 0;i < fav.size();i++) {

        //loading pic
        string path = fav[i].path;
        for (int j = 0;j < path.size();j++) {
            if (path[j] == '*') {
                path[j] = ' ';
            }
        }
        fav[i].path = path;


        if (fav[i].user_id == userid_adoption) {
            int y2 = 475;
            fav[i].name_text.setFont(font);
            fav[i].id_text.setFont(font);
            fav[i].req_text.setFont(font);

            fav[i].req_box.setTexture(tex_box);
            fav[i].req_box.setScale(0.5, 0.5);

            fav[i].under.setTexture(under_tex);
            fav[i].under.setPosition(x_below + scroll_fav, y_below);

            fav[i].remove.setPosition(x_below + scroll_fav + 265, 265);
            x_below += 415;

            fav[i].remove.setTexture(remove_fav_tex);
            fav[i].remove.setScale(0.3, 0.3);


            fav[i].loadImage();
            fav[i].photo.setPosition(x + scroll_fav + 45, y);

            fav[i].name_text.setString("name : " + fav[i].name);
            fav[i].name_text.setFillColor(Color(70, 40, 10));
            fav[i].name_text.setCharacterSize(32);
            fav[i].name_text.setPosition(x + scroll_fav + 10, y2 += 50);

            fav[i].id_text.setString("id : " + fav[i].id);
            fav[i].id_text.setFillColor(Color(70, 40, 10));
            fav[i].id_text.setCharacterSize(32);
            fav[i].id_text.setPosition(x + scroll_fav + 10, y2 += 50);

            fav[i].req_box.setPosition(x + scroll_fav + 25, y2 += 50);

            fav[i].req_text.setCharacterSize(28);
            fav[i].req_text.setString("adopt");
            fav[i].req_text.setPosition(x + scroll_fav + 92, y2 += 13);

            x += 415;
        }
    }

}
void draw_fav() {
    window.draw(back_fav);
    window.draw(back_sp);
    window.draw(title_fav);
    window.draw(slide_sRight);
    window.draw(slide_sLeft);

    for (int i = 0;i < fav.size();i++) {
        if (fav[i].user_id == userid_adoption) {
            window.draw(fav[i].under);
            window.draw(fav[i].name_text);
            window.draw(fav[i].id_text);
            window.draw(fav[i].photo);
            window.draw(fav[i].remove);
            window.draw(fav[i].req_box);
            window.draw(fav[i].req_text);
        }
    }

}
void fav_page() {
    if (fav.empty()) {
        errorbox("you have no favourites", 50, 50);
        page_user();
    }
    while (window.isOpen()) {
        make_fav();

        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::MouseButtonPressed) {
                Vector2i mousePos = Mouse::getPosition(window);
                if (slide_sRight.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    scroll_fav -= 415;
                }
                if (slide_sLeft.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    scroll_fav += 415.0f;
                    if (scroll_fav > 0) scroll_fav = 0;

                }
                if (back_sp.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    page_user();
                }

                for (int i = 0;i < fav.size();i++) {

                    if (fav[i].req_box.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        // adoptionnn
                        for (int j = 0;j < pets.size();j++) {
                            if (fav[i].id == pets[j].id) {
                                string petId = pets[j].id;

                                // Check if this pet already has a pending request
                                if (hasPendingRequest(petId)) {
                                    errorbox("   " + petId + "  already has a \npending adoption request!", 20, 30);
                                    cout << petId << " already has a pending adoption request!" << endl;
                                }
                                else if (pets[j].availability == "unavailable") {
                                    errorbox(petId + " is unavailable", 55, 50);
                                }
                                else {
                                    int score = runAdoptionQuiz(petId);
                                    if (score >= 0) {
                                        cout << "Assessment completed for pet " << petId
                                            << " with score: " << score << endl;
                                    }
                                }

                            }
                        }
                    }



                    if (fav[i].remove.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        fav.erase(fav.begin() + i);
                        writefavourites(fav);

                    }
                }


            }

        }
        window.clear();

        draw_fav();
        window.display();
    }


}

// Info for adoption page
void info_page() {
    Texture back_info_tex;
    Sprite back_info;
    if (!back_info_tex.loadFromFile("info_page.png")) {
        cout << "Failed to load background\n";
    }
    back_info.setTexture(back_info_tex);


    if (!back_tex.loadFromFile("back.png")) {
        cout << "Failed to load button\n";
    }

    back_sp.setTexture(back_tex);
    back_sp.setScale(0.35, 0.35);
    back_sp.setPosition(1200, 20);

    while (window.isOpen()) {
    

        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::MouseButtonPressed) {
                Vector2i mousePos = Mouse::getPosition(window);
                if (back_sp.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    page_user();
                }
            }
        }
        window.clear();
        window.draw(back_info);
        window.draw(back_sp);
        window.display();
    }



}

// First user page and search 
void search(string search_value, vector<Pet>& search_output) {
    //DELETEEEEEE
   // search_value.resize(search_value.size() - 1);

    //  bool valid_search = false;
    search_output.clear();
    scrollOffset = 0;
    bool find_pet = false;
    for (int i = 0;i < search_value.size();i++) {

        if (search_value[i] >= 65 && search_value[i] <= 90) {
            search_value[i] += 32;
        }
    }
    if (search_value == "dog")search_value = "dogs";
    if (search_value == "cat")search_value = "cats";
    if (search_value == "bird")search_value = "birds";
    cout << "in search function" << search_value << endl;
    for (int i = 0;i < pets.size();i++) {
        if (search_value == pets[i].name || search_value == pets[i].availability || search_value == pets[i].breed
            || search_value == pets[i].health || search_value == pets[i].age || search_value == pets[i].id ||
            search_value == pets[i].species) {


            search_output.push_back(pets[i]);

            cout << "done";
            find_pet = true;
        }
    }
    if (!find_pet) {
        cout << "No pet found with the entered value" << endl;

        if (!font.loadFromFile("spring-egg.regular.ttf")) {
            cout << "Failed to load font\n";
        }
        not_found.setFont(font);
        not_found.setString("No pet found with the entered value");
        not_found.setCharacterSize(20);
        not_found.setPosition(410, 495);

        if (!tex_boxSearch.loadFromFile("filled_box.png")) {
            cout << "Failed to load image\n";
        }
        box_search.setTexture(tex_boxSearch);
        box_search.setScale(1.2, 1.2);
        box_search.setPosition(350, 450);

    }

}
void make_user() {
    // Texture filled_tex, empty_tex;
  
    if (!filled_tex.loadFromFile("filled_heart.png")) {
        cout << "Failed to load background\n";
    }
    if (!FAV_tex.loadFromFile("fav_user.png")) {
        cout << "Failed to load background\n";
    }
    if (!info_tex.loadFromFile("info.png")) {
        cout << "Failed to load background\n";
    }
    if (!empty_tex.loadFromFile("empty_heart.png")) {
        cout << "Failed to load background\n";
    }
    if (!font_search.loadFromFile("Prototype.ttf")) {
        cout << "Failed to load font\n";
    }

    if (!font.loadFromFile("spring-egg.regular.ttf")) {
        cout << "Failed to load font\n";
    }
    text_search.setFont(font_search);
    //text_search.setPosition(375, 75);
    text_search.setCharacterSize(40);
    text_search.setPosition(375, 63);

    if (!tex_slide_s.loadFromFile("slides.png")) {
        cout << "Failed to load background\n";
    }
    if (!back_tex.loadFromFile("back.png")) {
        cout << "Failed to load button\n";
    }

    below_tex.loadFromFile("bolow_user3.png");


    back_sp.setTexture(back_tex);
    back_sp.setScale(0.35, 0.35);
    back_sp.setPosition(1200, 20);


    slide_sRight.setTexture(tex_slide_s);
    slide_sRight.setScale(-0.3, 0.3);
    slide_sRight.setPosition(1290, 480);

    slide_sLeft.setTexture(tex_slide_s);
    slide_sLeft.setScale(0.3, 0.3);
    slide_sLeft.setPosition(10, 480);


    if (!tex_bell.loadFromFile("bell-removebg-preview.png")) {
        cout << "Failed to load image\n";
    }
    bell.setTexture(tex_bell);
    bell.setScale(0.5, 0.5);
    bell.setPosition(975, 20);

    //bell after notification
    bell_after_tex.loadFromFile("bell_not.png");
    bell_after.setTexture(bell_after_tex);
    bell_after.setScale(0.32, 0.32);
    bell_after.setPosition(965, 20);

    if (!tex_envelope.loadFromFile("e.png")) {
        cout << "Failed to load image\n";
    }
    envelope.setTexture(tex_envelope);
    envelope.setScale(0.55, 0.55);
    envelope.setPosition(1055, 22);

    FAV.setTexture(FAV_tex);
    FAV.setScale(0.3, 0.3);
    FAV.setPosition(975, 98);

    info.setTexture(info_tex);
    info.setScale(0.5, 0.5);
    info.setPosition(1062, 98);


    if (!textBackUser.loadFromFile("back_search.png")) {
        cout << "Failed to load background\n";
    }
    back_user.setTexture(textBackUser);



    if (!tex_box.loadFromFile("button.png")) {
        cout << "Failed to load background\n";
    }


    //for showing all pets ADDDDDDD
    int x1 = 80, y1 = 230;
    int x_below = 60, y_below = 210;
    for (int i = 0;i < pets.size();i++) {
        int y2 = 400;
        //loading pic
        string path = pets[i].image_path;
        for (int j = 0;j < path.size();j++) {
            if (path[j] == '*') {
                path[j] = ' ';
            }
        }
        pets[i].image_path = path;

        //for spaces in pets
        string year = pets[i].age;
        for (int j = 0;j < year.size();j++) {
            if (year[j] == '*') {
                year[j] = ' ';
            }
        }
        pets[i].age = year;

        //for favourite
        pets_array[i].filled_heart.setTexture(filled_tex);
        pets_array[i].filled_heart.setScale(0.7, 0.7);

        pets_array[i].empty_heart.setTexture(empty_tex);
        pets_array[i].empty_heart.setScale(0.7, 0.7);

        //
        pets_array[i].below.setTexture(below_tex);
        pets_array[i].below.setPosition(x_below + scrollOffset, y_below);
        pets_array[i].below.setScale(1.05, 1.07);
        x_below += 430;

        pets_array[i].box.setTexture(tex_box);
        pets_array[i].box.setScale(0.55, 0.55);

        pets_array[i].pet_name.setFont(font);
        pets_array[i].pet_id.setFont(font);
        pets_array[i].pet_breed.setFont(font);
        pets_array[i].pet_species.setFont(font);
        pets_array[i].pet_health.setFont(font);
        pets_array[i].pet_availability.setFont(font);
        pets_array[i].pet_age.setFont(font);
        pets_array[i].requesting.setFont(font);

        pets_array[i].age_value.setFont(font);
        pets_array[i].name_value.setFont(font);
        pets_array[i].breed_value.setFont(font);
        pets_array[i].species_value.setFont(font);
        pets_array[i].health_value.setFont(font);
        pets_array[i].id_value.setFont(font);

        //  Color brown(123, 63, 0);
        Color brown(70, 40, 10);

        pets_array[i].pet_name.setFillColor(brown);
        pets_array[i].pet_id.setFillColor(brown);
        pets_array[i].pet_breed.setFillColor(brown);
        pets_array[i].pet_species.setFillColor(brown);
        pets_array[i].pet_health.setFillColor(brown);
        pets_array[i].pet_availability.setFillColor(brown);
        pets_array[i].pet_age.setFillColor(brown);

        pets_array[i].pet_name.setString("Name: ");
        pets_array[i].pet_id.setString("ID: ");
        pets_array[i].pet_breed.setString("Breed: ");
        pets_array[i].pet_species.setString("Species: ");
        pets_array[i].pet_health.setString("Health: ");
        //  pets_array[i].pet_availability.setString("Availability: " + pets[i].availability);
        pets_array[i].pet_availability.setString(pets[i].availability);
        pets_array[i].pet_age.setString("Age: ");


        pets_array[i].name_value.setString(pets[i].name);
        pets_array[i].id_value.setString(pets[i].id);
        pets_array[i].breed_value.setString(pets[i].breed);
        pets_array[i].species_value.setString(pets[i].species);
        pets_array[i].health_value.setString(pets[i].health);
        pets_array[i].age_value.setString(pets[i].age);


        pets_array[i].name_value.setCharacterSize(20);
        pets_array[i].id_value.setCharacterSize(20);
        pets_array[i].age_value.setCharacterSize(20);
        pets_array[i].breed_value.setCharacterSize(20);
        pets_array[i].species_value.setCharacterSize(20);
        pets_array[i].health_value.setCharacterSize(20);


        pets_array[i].pet_name.setCharacterSize(20);
        pets_array[i].pet_id.setCharacterSize(20);
        pets_array[i].pet_age.setCharacterSize(20);
        pets_array[i].pet_breed.setCharacterSize(20);
        pets_array[i].pet_species.setCharacterSize(20);
        pets_array[i].pet_availability.setCharacterSize(23);
        pets_array[i].pet_health.setCharacterSize(20);

        pets[i].loadImage();
        pets[i].photo.setPosition(x1 + scrollOffset + 35, y1);

        //for fav
        pets_array[i].filled_heart.setPosition(x1 + scrollOffset, y1);
        pets_array[i].empty_heart.setPosition(x1 + scrollOffset, y1);

        pets_array[i].pet_name.setPosition(x1 + scrollOffset, y2 += 50);
        pets_array[i].name_value.setPosition(x1 + 80 + scrollOffset, y2);

        pets_array[i].pet_id.setPosition(x1 + scrollOffset, y2 += 50);
        pets_array[i].id_value.setPosition(x1 + 40 + scrollOffset, y2);

        pets_array[i].pet_age.setPosition(x1 + scrollOffset, y2 += 50);
        pets_array[i].age_value.setPosition(x1 + 58 + scrollOffset, y2);

        pets_array[i].pet_breed.setPosition(x1 + scrollOffset, y2 += 50);
        pets_array[i].breed_value.setPosition(x1 + 90 + scrollOffset, y2);

        pets_array[i].pet_species.setPosition(x1 + scrollOffset, y2 += 50);
        pets_array[i].species_value.setPosition(x1 + 115 + scrollOffset, y2);

        pets_array[i].pet_health.setPosition(x1 + scrollOffset, y2 += 50);
        pets_array[i].health_value.setPosition(x1 + 100 + scrollOffset, y2);

        pets_array[i].pet_availability.setPosition(x1 + scrollOffset, y2 += 50);

        pets_array[i].box.setPosition(x1 + scrollOffset + 12, y2 += 50);
        pets_array[i].requesting.setCharacterSize(18);
        pets_array[i].requesting.setString("request adoption");
        pets_array[i].requesting.setPosition(x1 + 40 + scrollOffset, y2 += 22);
        x1 += 430;



    }

    if (!search_out.empty()) {
        //for showing pets of the search
        int x_below1 = 60, y_below1 = 210;
        int x = 80, y = 230;
        for (int i = 0;i < search_out.size();i++) {
            int y1 = 400;

            string path = search_out[i].image_path;
            for (int j = 0;j < path.size();j++) {
                if (path[j] == '*') {
                    path[j] = ' ';
                }
            }
            search_out[i].image_path = path;

            //for spaces in pets
            string year = search_out[i].age;
            for (int j = 0;j < year.size();j++) {
                if (year[j] == '*') {
                    year[j] = ' ';
                }
            }
            search_out[i].age = year;

            search_array[i].box.setTexture(tex_box);
            search_array[i].box.setScale(0.55, 0.55);

            search_array[i].filled_heart.setTexture(filled_tex);
            search_array[i].filled_heart.setScale(0.7, 0.7);

            search_array[i].empty_heart.setTexture(empty_tex);
            search_array[i].empty_heart.setScale(0.7, 0.7);

            search_array[i].below.setTexture(below_tex);
            search_array[i].below.setPosition(x_below1 + scrollOffset, y_below1);
            search_array[i].below.setScale(1.05, 1.07);
            x_below1 += 430;

            search_array[i].pet_name.setFont(font);
            search_array[i].pet_id.setFont(font);
            search_array[i].pet_breed.setFont(font);
            search_array[i].pet_species.setFont(font);
            search_array[i].pet_health.setFont(font);
            search_array[i].pet_availability.setFont(font);
            search_array[i].pet_age.setFont(font);
            search_array[i].requesting.setFont(font);


            search_array[i].age_value.setFont(font);
            search_array[i].name_value.setFont(font);
            search_array[i].breed_value.setFont(font);
            search_array[i].species_value.setFont(font);
            search_array[i].health_value.setFont(font);
            search_array[i].id_value.setFont(font);


            search_array[i].name_value.setCharacterSize(20);
            search_array[i].id_value.setCharacterSize(20);
            search_array[i].age_value.setCharacterSize(20);
            search_array[i].breed_value.setCharacterSize(20);
            search_array[i].species_value.setCharacterSize(20);
            search_array[i].health_value.setCharacterSize(20);

            // Color brown(123, 63, 0);
            Color brown(70, 40, 10);
            search_array[i].pet_name.setFillColor(brown);
            search_array[i].pet_id.setFillColor(brown);
            search_array[i].pet_breed.setFillColor(brown);
            search_array[i].pet_species.setFillColor(brown);
            search_array[i].pet_health.setFillColor(brown);
            search_array[i].pet_availability.setFillColor(brown);
            search_array[i].pet_age.setFillColor(brown);

            search_array[i].pet_name.setString("Name: ");
            search_array[i].pet_id.setString("ID: ");
            search_array[i].pet_breed.setString("Breed: ");
            search_array[i].pet_species.setString("Species: ");
            search_array[i].pet_health.setString("Health: ");
            search_array[i].pet_availability.setString(search_out[i].availability);
            search_array[i].pet_age.setString("Age: ");


            search_array[i].name_value.setString(search_out[i].name);
            search_array[i].id_value.setString(search_out[i].id);
            search_array[i].breed_value.setString(search_out[i].breed);
            search_array[i].species_value.setString(search_out[i].species);
            search_array[i].health_value.setString(search_out[i].health);
            search_array[i].age_value.setString(search_out[i].age);


            search_array[i].pet_name.setCharacterSize(20);
            search_array[i].pet_id.setCharacterSize(20);
            search_array[i].pet_age.setCharacterSize(20);
            search_array[i].pet_breed.setCharacterSize(20);
            search_array[i].pet_species.setCharacterSize(20);
            search_array[i].pet_availability.setCharacterSize(23);
            search_array[i].pet_health.setCharacterSize(20);

            search_out[i].loadImage();
            search_out[i].photo.setPosition(x + scrollOffset + 35, y);

            search_array[i].filled_heart.setPosition(x + scrollOffset, y);
            search_array[i].empty_heart.setPosition(x + scrollOffset, y);

            search_array[i].pet_name.setPosition(x + scrollOffset, y1 += 50);
            search_array[i].name_value.setPosition(x + 80 + scrollOffset, y1);

            search_array[i].pet_id.setPosition(x + scrollOffset, y1 += 50);
            search_array[i].id_value.setPosition(x + 40 + scrollOffset, y1);

            search_array[i].pet_age.setPosition(x + scrollOffset, y1 += 50);
            search_array[i].age_value.setPosition(x + 58 + scrollOffset, y1);

            search_array[i].pet_breed.setPosition(x + scrollOffset, y1 += 50);
            search_array[i].breed_value.setPosition(x + 90 + scrollOffset, y1);

            search_array[i].pet_species.setPosition(x + scrollOffset, y1 += 50);
            search_array[i].species_value.setPosition(x + 115 + scrollOffset, y1);

            search_array[i].pet_health.setPosition(x + scrollOffset, y1 += 50);
            search_array[i].health_value.setPosition(x + 100 + scrollOffset, y1);

            search_array[i].pet_availability.setPosition(x + scrollOffset, y1 += 50);

            search_array[i].box.setPosition(x + scrollOffset + 12, y1 += 50);
            search_array[i].requesting.setCharacterSize(18);
            search_array[i].requesting.setString("request adoption");
            search_array[i].requesting.setPosition(x + 40 + scrollOffset, y1 += 22);
            x += 430;



        }


    }


}
void drawUser() {
    window.draw(back_user);

 
    if (not_vector.empty() || (cnt_notification==0)) {
        window.draw(bell);
    }
    else {
        window.draw(bell_after);
    }

    window.draw(slide_sLeft);
    window.draw(slide_sRight);
    window.draw(envelope);
    window.draw(back_sp);
    window.draw(text_search);

    window.draw(FAV);
    window.draw(info);

    if (!search_out.empty()) {


        for (int i = 0;i < search_out.size();i++) {
            window.draw(search_array[i].below);
            window.draw(search_out[i].photo);
            window.draw(search_array[i].pet_name);
            window.draw(search_array[i].pet_id);
            window.draw(search_array[i].pet_age);
            window.draw(search_array[i].pet_health);
            window.draw(search_array[i].pet_availability);
            window.draw(search_array[i].pet_breed);
            window.draw(search_array[i].pet_species);
            window.draw(search_array[i].box);
            window.draw(search_array[i].requesting);
            window.draw(search_array[i].name_value);
            window.draw(search_array[i].id_value);
            window.draw(search_array[i].age_value);
            window.draw(search_array[i].health_value);
            window.draw(search_array[i].breed_value);
            window.draw(search_array[i].species_value);


            window.draw(search_array[i].empty_heart);

            for (int j = 0;j < fav.size();j++) {
                if (fav[j].user_id == userid_adoption) {
                    if (fav[j].id == search_out[i].id) {
                        window.draw(search_array[i].filled_heart);
                    }
                }
            }

        }
    }
    else if (search_out.empty() && searching) {
        window.draw(box_search);
        window.draw(not_found);

    }
    if (!searching) {
        for (int i = 0;i < pets.size();i++) {
            window.draw(pets_array[i].below);
            window.draw(pets[i].photo);
            window.draw(pets_array[i].pet_name);
            window.draw(pets_array[i].pet_id);
            window.draw(pets_array[i].pet_age);
            window.draw(pets_array[i].pet_health);
            window.draw(pets_array[i].pet_availability);
            window.draw(pets_array[i].pet_breed);
            window.draw(pets_array[i].pet_species);
            window.draw(pets_array[i].box);
            window.draw(pets_array[i].requesting);
            window.draw(pets_array[i].name_value);
            window.draw(pets_array[i].id_value);
            window.draw(pets_array[i].age_value);
            window.draw(pets_array[i].health_value);
            window.draw(pets_array[i].breed_value);
            window.draw(pets_array[i].species_value);

            window.draw(pets_array[i].empty_heart);
            for (int j = 0;j < fav.size();j++) {
                if (fav[j].user_id == userid_adoption) {
                    if (fav[j].id == pets[i].id) {
                        window.draw(pets_array[i].filled_heart);
                    }
                }
            }
        }


    }

}
void page_user() {
    favourite thisfav;
    scrollOffset = 0;

    //to count the notifications for a specific user
    for (int i = 0;i < not_vector.size();i++) {
        if (not_vector[i].user_id == userid_adoption) {
            cnt_notification++;
        }
    }
  //  cout << "no of notication here is " << cnt_notification << endl;

    while (window.isOpen()) {
        make_user();
        text_search.setString(input_search);

        Event event;
      
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::TextEntered) {
                if (event.text.unicode >= 32 && event.text.unicode < 127) {
                    input_search += static_cast<char>(event.text.unicode);
                }
            }

            if (Keyboard::isKeyPressed(Keyboard::BackSpace) && input_search.size() > 0) {
                //  input_search.resize(input_search.size() - 1);
                input_search.pop_back();
                text_search.setString(input_search);
            }

            if (event.type == Event::KeyReleased && event.key.code == Keyboard::Enter) {
                searching = true;
                search(input_search, search_out);
                input_search.clear();
            }

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));

                // Handle slider buttons
                if (slide_sLeft.getGlobalBounds().contains(mousePos)) {
                    scrollOffset += 430.0f;
                    if (scrollOffset > 0) scrollOffset = 0;
                }
                else if (slide_sRight.getGlobalBounds().contains(mousePos)) {
                    scrollOffset -= 430.0f;
                }
                // Handle other buttons
                else if (bell.getGlobalBounds().contains(mousePos)) {
                    showNotificationsScreen();
                }
                else if (envelope.getGlobalBounds().contains(mousePos)) {
                    viewrequestpage();

                }
                else if (FAV.getGlobalBounds().contains(mousePos)) {
                    fav_page();
                }
                else if (info.getGlobalBounds().contains(mousePos)) {
                    ///HELP PAGEEE;
                    info_page();
                }
                else if (back_sp.getGlobalBounds().contains(mousePos)) {
                    if (searching) {
                        searching = false;
                    }
                    else {
                        firstpage();
                  
                    }

                }
                // Handle pet box clicks "adoption request"
                else {
                    bool clickedPet = false;

                    // Check regular pets first
                    if (!searching) {
                        for (int i = 0; i < pets.size(); i++) {
                            //for fav
                            if (pets_array[i].empty_heart.getGlobalBounds().contains(mousePos)) {
                                bool found_fav = false;
                                for (int j = 0;j < fav.size();j++) {
                                    if (fav[j].id == pets[i].id) {
                                        found_fav = true;
                                    }
                                }
                                if (!found_fav) {
                                    thisfav.user_id = userid_adoption;
                                    thisfav.id = pets[i].id;
                                    thisfav.name = pets[i].name;
                                    thisfav.path = pets[i].image_path;
                                    fav.push_back(thisfav);
                                    writefavourites(fav);

                                    select_fav = true;
                                }


                            }

                            if (pets_array[i].box.getGlobalBounds().contains(mousePos)) {
                                string petId = pets[i].id;

                                // Check if this pet already has a pending request
                                if (hasPendingRequest(petId)) {
                                    errorbox("   " + petId + "  already has a \npending adoption request!", 20, 30);
                                    cout << petId << " already has a pending adoption request!" << endl;
                                }
                                else if (pets[i].availability == "unavailable") {
                                    errorbox(petId + " is unavailable", 55, 50);
                                }
                                else {
                                    int score = runAdoptionQuiz(petId);
                                    if (score >= 0) {
                                        cout << "Assessment completed for pet " << petId
                                            << " with score: " << score << endl;
                                    }
                                }
                                clickedPet = true;
                                break;
                            }
                        }
                    }

                    // Check search results if in search mode and no regular pet clicked
                    if (!clickedPet && !search_out.empty()) {
                        for (int i = 0; i < search_out.size(); i++) {

                            if (search_array[i].empty_heart.getGlobalBounds().contains(mousePos)) {
                                bool found_fav = false;
                                for (int j = 0;j < fav.size();j++) {
                                    if (fav[j].id == search_out[i].id) {
                                        found_fav = true;
                                    }
                                }
                                if (!found_fav) {
                                    thisfav.user_id = userid_adoption;
                                    thisfav.id = search_out[i].id;
                                    thisfav.name = search_out[i].name;
                                    thisfav.path = search_out[i].image_path;
                                    fav.push_back(thisfav);
                                    writefavourites(fav);
                                    select_fav = true;
                                }


                            }



                            if (search_array[i].box.getGlobalBounds().contains(mousePos)) {
                                string petId = search_out[i].id;

                                // Check if this pet already has a pending request
                                if (hasPendingRequest(petId)) {
                                    errorbox("   " + petId + "  already has a \npending adoption request!", 20, 30);

                                    cout << "Pet " << petId << " already has a pending adoption request!" << endl;
                                }
                                else if (search_out[i].availability == "unavailable") {
                                    errorbox(petId + " is unavailable", 55, 50);
                                }
                                else {
                                    int score = runAdoptionQuiz(petId);
                                    if (score >= 0) {
                                        cout << "Assessment completed for pet " << petId
                                            << " with score: " << score << endl;
                                    }
                                }
                                break;
                            }
                        }
                    }
                }
            }
        }

        window.clear();
        drawUser();
        //  window.draw(text_search);
        window.display();
    }
}
