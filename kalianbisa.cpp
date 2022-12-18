// Online C++ compiler to run C++ program online
#include <iostream>
#include <map>
#include <type_traits>
using namespace std;

class User {
    public:
        string username;
        string password;
        int type;
};

class Campaign {
    public:
        int id;
        User user;
        string judul;
        int target;
        int pencapaian;
};

class Donation {
    public:
        int id;
        int campaign_id;
        int besaran;
        User user;
};

map<string, User> users;
map<int, Campaign> campaigns;
map<int, Donation> donations;
User * login_user = NULL;
int increment = 1;

void regis() {
    User user;
    printf("Masukkan username: ");
    cin >> user.username;
    printf("Buat password: ");
    cin >> user.password;
    bool is_type_correct = false;
    while (!is_type_correct) {
        printf("Pilih tipe user\n");
        printf("1. Fundraiser\n2. Donatur\nTipe user: ");
        cin >> user.type;
        if (user.type == 1 || user.type == 2) {
            is_type_correct = true;
        } else {
            printf("Tipe user salah\n");
        }
    }
    users.insert(pair<string, User>(user.username, user));
    printf("User dengan username \"%s\" berhasil dibuat.\n", user.username.c_str());
}

int login() {
    bool has_login = false;
    while (!has_login) {
        User user;
        printf("Username: ");
        cin >> user.username;
        printf("Password: ");
        cin >> user.password;
        if (users.count(user.username) == 0) {
            printf("User %s tidak ditemukan\n", user.username.c_str());
            printf("Coba login lagi? (y/n): ");
            char yes;
            cin >> yes;
            if (yes != 'y') {
                return 0;
            }
        } else {
            User * saved_user = &users[user.username];
            if (saved_user->password == user.password) {
                has_login = true;
                login_user = saved_user;
            } else {
                printf("Username dan password salah\n");
            }
        }
    }
    return 1;
}

void logout() {
    login_user = NULL;
}

void tampilkan_daftar_campaign() {
    if (campaigns.size() > 0) {
        map<int, Campaign>::iterator it;
        printf("Daftar campaign\n");
        printf("------------\n");
        printf("Id\tJudul\tUser\tTarget\tPencapaian\n");
        printf("------------\n");
        for (it = campaigns.begin(); it != campaigns.end(); it++) {
            Campaign camp = it->second;
            printf("%d\t", camp.id);
            printf("%s\t", camp.judul.c_str());
            printf("%s\t", camp.user.username.c_str());
            printf("%d\t", camp.target);
            printf("%d\t", camp.pencapaian);
            printf("\n");
        }
    } else {
        printf("Belum ada campaign\n");
    }
}
void buat_campaign() {
    Campaign campaign;
    campaign.id = increment++;
    User user;
    user.username = login_user->username;
    campaign.user = user;
    campaign.pencapaian = 0;
    printf("------------\n");
    printf("Judul campaign: ");
    cin.ignore();
    getline(cin, campaign.judul);
    //cin >> campaign.judul; <-- gak bisa spasi
    printf("Target campaign: ");
    cin >> campaign.target;
    campaigns.insert(pair<int, Campaign>(campaign.id, campaign));
}
void hapus_campaign() {
    int id;
    printf("Masukkan id campaign: ");
    cin >> id;
    if (campaigns.count(id) == 1) {
        Campaign camp = campaigns[id];
        printf("Hapus campaign \"%s\"? (y/n): ", camp.judul.c_str());
        char yes;
        cin >> yes;
        // jika y, hapus campaign dari map campaigns dan tampilkan pesan campain sudah dihapus
        // jika n, keluar
        printf("\n");
    } else {
        printf("Campaign tidak ada\n");
    }
}
void tampilkan_fundraiser_menu() {
    bool is_login = true;
    printf("============\n");
    printf("Hi, fundraiser %s.\n", login_user->username.c_str());
    while(is_login) {
        printf("============\n");
        printf("1. Lihat daftar campaign\n");
        printf("2. Buat campaign\n");
        printf("3. Hapus campaign\n");
        printf("0. Logout\n");
        printf("Pilih menu: ");
        int menu;
        cin >> menu;
        if (menu == 1) {
            tampilkan_daftar_campaign();
        } else if (menu == 2) {
            buat_campaign();
        } else if (menu == 3) {
            hapus_campaign();
        } else if (menu == 0) {
            return logout();
        } else {
            printf("Menu tidak ada\n");
        }
    }
}

void tampilkan_donatur_menu() {
    // TODO tugas orang muda ;)
}

int init() {
    int menu;
    printf("============\n");
    printf("Silahkan lakukan login akun terlebih dahulu\n");
    while (true) {
        printf("============\n");
        printf("1. Login\n");
        printf("2. Registrasi\n");
        printf("0. Tutup applikasi\n");
        printf("Pilih menu : ");
        cin >> menu;
        if (menu == 1 && login() == 1) {
            return 1;
        } else if (menu == 2) {
            regis();
        } else if (menu == 0) {
            return 0;
        } else {
            printf("Menu tidak ada\n");
        }
    }
}

int main() {
    // create super admin
    User super;
    super.username = "super";
    super.password = "rahasia";
    super.type = 1;
    users.insert(pair<string, User>("super", super));
    // 
    printf("Selamat Datang di KalianBisan\n");
    while(init()) {
        if (login_user->type == 1) {
            tampilkan_fundraiser_menu();
        } else {
            tampilkan_donatur_menu();
        }
    }
    printf("Good bye!\n");
    return 0;
}
