/*
CRM per impresa di assicurazioni
InsuraPro Solutions si dedica a migliorare l'efficienza e la qualità del servizio clienti per le imprese di assicurazioni, sviluppando un avanzato sistema di Customer Relationship Management (CRM) che facilita la gestione delle informazioni sui clienti e delle loro interazioni con l'azienda.

Le imprese di assicurazioni necessitano di un metodo sistematico e centralizzato per gestire le informazioni sui clienti e tracciare le interazioni. Molti sistemi attuali sono frammentati o non user-friendly, ostacolando l’efficacia operativa e la soddisfazione del cliente.

InsuraPro Solutions offrirà un’applicazione console interattiva sviluppata in C++ che permetterà agli utenti di gestire le informazioni sui clienti e le loro interazioni in modo efficiente e intuitivo, migliorando così il servizio clienti e la gestione interna.

Requisiti del Progetto:
    
    1. OOP in C++: Implementare i concetti di OOP per una struttura robusta e flessibile.
    2. Struttura Dati: Creare una struttura di dati per memorizzare le informazioni sui clienti e le loro interazioni.
    3. Interfaccia Utente: Sviluppare un’interfaccia da linea di comando interattiva e intuitiva.
    4. Funzionalità:
        4.1 Aggiunta di un Cliente: Inserimento di nuovi clienti nel CRM.
        4.2 Visualizzazione dei Clienti: Visualizzare tutti i clienti presenti.
        4.3 Modifica di un Cliente: Modificare i dettagli di un cliente esistente.
        4.4 Eliminazione di un Cliente: Rimuovere clienti dal CRM.
        4.5 Ricerca di un Cliente: Cercare clienti per nome o cognome.
        4.6 Gestione delle Interazioni: Aggiungere, visualizzare e cercare interazioni per ogni cliente (per interazioni si intendono gli appuntamenti da parte della forza vendita e i contratti stipulati).
        4.7 Salvataggio e Caricamento Dati: Salvare i dati dei clienti e delle interazioni in un file (testo o CSV) e caricarli all’avvio.

Interfaccia Utente: L’interfaccia sarà basata su riga di comando, con un menu principale che offre opzioni chiare per tutte le operazioni necessarie, assicurando un'esperienza utente fluida e accessibile.*/


#include <bits/stdc++.h>
using namespace std;


// ======================================================
// =============== CLASSE INTERACTION ===================
// ======================================================

class Interaction{
    protected:
        static int interaction_counter;
        int interaction_ID;
        string date;
        int client_ID;
        bool is_completed;
    
    public:
        //costruttore specifico per caricamento da file
        Interaction(int _interaction_ID, string _date, int _client_ID, bool _is_completed = false){
            interaction_ID = _interaction_ID;
            date = _date;
            client_ID = _client_ID;
            is_completed = _is_completed;
            //aggiorna contatore se necessario
            if (_interaction_ID > interaction_counter) {
                interaction_counter = _interaction_ID;
            }
        }

        //costruttore specifico per nuove interazioni
        Interaction(string _date, int _client_ID, bool _is_completed = false){
            date = _date;
            client_ID = _client_ID;
            is_completed = _is_completed;
            interaction_ID = ++interaction_counter; //incrementa contatore per ogni nuova interazione
        }

        //metodi getter
        int get_interaction_ID(){ 
            return interaction_ID; 
        }
        string get_date(){ 
            return date; 
        }
        int get_client_ID(){ 
            return client_ID; 
        }
        bool get_is_completed(){ 
            return is_completed; 
        }

        //metodi setter
        void set_date(string _date){
            date = _date;
        }
        void set_is_completed(bool _is_completed){
            is_completed = _is_completed;
        }

        //funzione virtuale per tipologia di operazione
        virtual void interaction_type() = 0;

        //override di funzione visualizza()
        virtual void visualizza(){
            cout << "ID Interazione: " << get_interaction_ID() << endl;
            cout << "Data Interazione: " << get_date() << endl;
            cout << "ID cliente: " << get_client_ID() << endl;
            cout << "Stato Interazione: " << (get_is_completed() ? "Completed" : "Not Completed") << endl;
        }

        friend class CRM;        
};

//inizializzazione del contatore per interazioni
int Interaction::interaction_counter = 0;



// ======================================================
// ============ CLASSE FIGLIA APPOINTMENT ===============
// ======================================================

class Appointment : public Interaction{
    private:
        string place, time, info;

    public:
        //costruttore specifico per caricamento da file
        Appointment(int _interaction_ID, string _date, int _client_ID, string _place, string _time, string _info, bool _is_completed = false)
        : Interaction(_interaction_ID, _date, _client_ID, _is_completed){
            place = _place;
            time = _time;
            info = _info;
        }

        //costruttore specifico per nuovi appuntamenti
        Appointment(string _date, int _client_ID, string _place, string _time, string _info, bool _is_completed = false)
        : Interaction(_date, _client_ID, _is_completed){
            place = _place;
            time = _time;
            info = _info;
        }

        //metodi getter
        string get_place(){
            return place;
        }
        string get_time(){
            return time;
        }
        string get_info(){
            return info;
        }

        //metodi setter
        void set_place(string _place){
            place = _place;
        }
        void set_time(string _time){
            time = _time;
        }
        void set_info(string _info){
            info = _info;
        }

        //override di funzione
        void visualizza(){
            cout << "--- APPUNTAMENTO ---\n" << endl;
            Interaction::visualizza();
            cout << "Ora Appuntamento: " << get_time() << endl; 
            cout << "Luogo Appuntamento: " << get_place() << endl; 
            cout << "Info Appuntamento: " << get_info() << endl; 
        }

        //override di funzione
        void interaction_type(){
           cout << "Tipo di Interazione: Appuntamento" << endl;
        }
        
        friend class CRM;
};



// ======================================================
// ============= CLASSE FIGLIA CONTRACT =================
// ======================================================

class Contract : public Interaction{
    private:
        string contract_category; //prodotto o servizio
        float total_cost; //costo complessivo contratto
        bool is_recurring; //true=recurring false=one-shot
        string closing_date; // data chiusura contratto

    public:
        //costruttore specifico per caricamento da file
        Contract(int _interaction_ID, string _date, int _client_ID, string _contract_category, float _total_cost, bool _is_recurring, string _closing_date)
        : Interaction(_interaction_ID, _date, _client_ID){
            contract_category = _contract_category;
            total_cost = _total_cost;
            is_recurring = _is_recurring;
            closing_date = _closing_date;
        }

        //costruttore specifico per nuovo contratto
        Contract(string _date, int _client_ID, string _contract_category, float _total_cost, bool _is_recurring, string _closing_date)
        : Interaction(_date, _client_ID){
            contract_category = _contract_category;
            total_cost = _total_cost;
            is_recurring = _is_recurring;
            closing_date = _closing_date;
        }

        //metodi getter
        string get_contract_category(){
            return contract_category;
        }
        float get_total_cost(){
            return total_cost;
        }
        bool get_is_recurring(){
            return is_recurring;
        }
        string get_closing_date(){
            return closing_date;
        }

        //metodi setter
        void set_contract_category(string _contract_category){
            contract_category = _contract_category;
        }
        void set_total_cost(float _total_cost){
            total_cost = _total_cost;
        }
        void set_is_recurring(bool _is_recurring){
            is_recurring = _is_recurring;
        }
        void set_closing_date(string _closing_date){
            closing_date = _closing_date;
        }

        //override di funzione
        void visualizza(){
            cout << "--- CONTRATTO ---\n" << endl;
            Interaction::visualizza();
            cout << "Categoria contratto: " << get_contract_category() << endl; 
            cout << "Valore complessivo: " << get_total_cost() << "euro" << endl; 
            cout << "Metodo di pagamento: " << (get_is_recurring() ? "Recurring" : "One-shot") << endl; 
            cout << "Data chiusura: " << get_closing_date() << endl; 
        }

        //override di funzione
        void interaction_type(){
            cout << "Tipo di Interazione: Contratto" << endl;
        }

        friend class CRM;
};



// ======================================================
// ================== CLASSE CLIENT =====================
// ======================================================

class Client{
    private:
        static int client_counter;
        int client_ID;
        string name, surname, email;
        list<Interaction*> interactions; 
        //list è un contenitore della stl, implementa una lista in cui ogni elemento contiene un puntatore al successivo e precedente, per gestire interazioni = struttura dati in memoria che mantiene tutti i clienti del CRM e le loro interazioni

    public:
        //costruttore specifico
        Client(string _name, string _surname, string _email){
            name = _name;
            surname = _surname;
            email = _email;
            client_ID = ++client_counter; //contatore per generare l'ID
        }

        //metodi getter
        int get_client_ID(){ 
            return client_ID; 
        }
        string get_name(){
            return name;
        }
        string get_surname(){
            return surname;
        }
        string get_email(){
            return email;
        }

        //metodi setter
        void set_name(string _name){
            name = _name;
        }
        void set_surname(string _surname){
            surname = _surname;
        }
        void set_email(string _email){
            email = _email;
        }

        //gestione delle interazioni con il client:
        //per aggiungere interazione alla lista delle interazioni cliente tramite puntatore, appesa in coda alla lista con push.back()
        void add_interaction(Interaction* interaction){
            interactions.push_back(interaction);
        }
        
        //per rimuovere interazione dalla lista delle interazioni cliente,ciclo per cercare interazione tramite ID, se interazione esiste viene rimossa 
        void remove_interaction(int interaction_ID) {
            for (auto& interaction : interactions) {
                if (interaction->get_interaction_ID() == interaction_ID) {
                    delete interaction; //libera la memoria
                    interactions.remove(interaction); //rimuove interazione da list
                    break; 
                }
            }
        }

        //visualizza dati del cliente
        void visualizza(){
            cout << "\n=== Cliente ===\n" << endl;
            cout << "ID: " << get_client_ID() << endl;
            cout << "Nome: " << get_name() << endl;
            cout << "Cognome: " << get_surname() << endl;
            cout << "Email: " << get_email() << endl;
            cout << "\n--- Interazioni ---\n" << endl;
            if (interactions.empty()) {
                cout << "Nessuna interazione presente." << endl;
            } else {
                for(const auto& interaction:interactions){
                    if (interaction) {
                        interaction->visualizza();
                        cout << "--------------------------------\n";
                    }
                }
            }
        }

        list<Interaction*>& get_interactions(){
            return interactions;
        }

        //friend class con class CRM
        friend class CRM;
};

int Client::client_counter = 0;


// ============================================
// =====funzione normalize_date()==============
// ============================================
string normalize_date(const string& input_date){
    string normalized_date;
    char norm_array[11]; //DD-YY-YYYY + terminatore

    int day, month, year;
    char sep1, sep2;

    if (sscanf(input_date.c_str(), "%d%c%d%c%d", &day, &sep1, &month, &sep2, &year) == 5) {
        //se anno ha solo 2 cifre aggiunge "20" davanti
        if (year < 100) {
            year += 2000;
        }

        //normalizza data nel formato DD-MM-YYYY
        snprintf(norm_array, sizeof(norm_array), "%02d-%02d-%04d", day, month, year);
        normalized_date = norm_array;
    } else {
        // Se la data non è valida, restituisci una stringa vuota
        normalized_date = "";
    }

    return normalized_date;

}


// ======================================================
// ================== CLASSE CRM ========================
// ======================================================

class CRM{
    private:
        //puntatore al file
        FILE* file;
        //percorso al file
        const char* percorso_al_file;
        list<Client*>clients;

    public:
        //costruttore default
        CRM(){
            percorso_al_file = "./CRM.csv";
            file = fopen(percorso_al_file, "a+"); //lettura e scrittura, mantiene il contenuto se file già esiste, crea il file se non esiste

            if (file == nullptr){ //== NULL
                cout << "\nErrore nell'apertura o creazione del file." << endl;//file bloccato o non disponibile
            }

            //verifica se file vuoto
            fseek(file, 0, SEEK_END); //andiamo alla fine del file
            if (ftell(file) == 0) { //otteniamo posizione corrente, se 0 vuol dire che il file è vuoto
                fprintf(file, "ID Cliente,Nome,Cognome,Email,ID Interazione,Data Interazione,Stato Interazione,Tipo Interazione,Ora Appuntamento,Luogo Appuntamento,Note Appuntamento,Categoria Contratto,Valore Complessivo Contratto,Metodo Pagamento Contratto,Data Chiusura Contratto\n"); //scriviamo header sul file
            }
            fclose(file);

            load_crm(); //carica i dati esistenti
        }



    // -------------------------------------------------------
    //----------------- METODI SPECIFICI -------------------
    // -------------------------------------------------------
    

    //----------------- Caricare i dati all'avvio del programma -------------------
        void load_crm(){
            file = fopen(percorso_al_file, "r");
            if (file == nullptr) {
                cout << "\nErrore nell'apertura del file " << percorso_al_file << ". Verificare che il file sia accessibile." << endl;
                return;
            }

            //array per leggere le righe
            char line[2000];
            //salta header (già presente)
            fgets(line, sizeof(line), file);

            int max_interaction_id = 0; //traccia ID massimo delle interazioni
            clients.clear(); //pulisce list per evitare duplicati

            //lettura del file riga per riga
            while (fgets(line, sizeof(line), file)) {
                // if (strlen(line) == 0) {
                //     continue;
                // }
                //rimuovi spazi bianchi e newline da fine riga altrimenti genera righe vuote
                size_t len = strlen(line);
                while (len > 0 && (line[len-1] == '\n' || line[len-1] == '\r' || line[len-1] == ' ')) {
                    line[--len] = '\0';
                }
                
                //salta le righe effettivamente vuote
                if (len == 0 || line[0] == '\0' || line[0] == '\n' || line[0] == '\r') {
                    continue;
                }
                        
                //attributi per cliente
                int client_id;
                string name, surname, email;
                
                //attributi per interazione
                int interaction_id;
                string date, type;
                bool is_completed;
                
                //attributi per appuntamento
                string time, place, info;
                
                //attributi per contratto
                string category, closing_date;
                bool is_recurring;
                float cost;

                //strtok per suddividere la riga in token
                char* token = strtok(line, ",");
                if (token) client_id = atoi(token);

                token = strtok(nullptr, ",");
                if (token) name = string(token);

                token = strtok(nullptr, ",");
                if (token) surname = string(token);

                token = strtok(nullptr, ",");
                if (token) email = string(token);

                token = strtok(nullptr, ",");
                if (token) interaction_id = atoi(token);

                token = strtok(nullptr, ",");
                if (token) date = string(token);

                token = strtok(nullptr, ",");
                if (token) is_completed = (strcmp(token, "Completed") == 0);

                token = strtok(nullptr, ",");
                if (token) type = string(token);

                //ricerca del cliente in list clients
                Client* client = nullptr;
                for (auto& existing_client : clients) {
                    if (existing_client->get_client_ID() == client_id) {
                        client = existing_client;
                        break;
                    }
                }
                
                //se cliente non esiste lo crea
                if (!client) {
                    client = new Client(name, surname, email);
                    if (client == nullptr) { //verifica su puntatore
                        cout << "\nErrore: impossibile allocare memoria per caricare i clienti." << endl;
                        return;
                    }
                    clients.push_back(client);
                }

                if (interaction_id > max_interaction_id) {
                    max_interaction_id = interaction_id;
                }
        
                if (client && interaction_id != 0) {
                    Interaction* new_interaction = nullptr;

                    //caricate interazioni cliente in base al tipo
                    if (type == "Appuntamento") {
                        token = strtok(nullptr, ",");
                        if (token) time = string(token);

                        token = strtok(nullptr, ",");
                        if (token) place = string(token);

                        token = strtok(nullptr, ",");
                        if (token) info = string(token);
            
                        new_interaction = new Appointment(interaction_id, date, client_id, place, time, info, is_completed);

                    } else if (type == "Contratto") {
                        token = strtok(nullptr, ",");
                        if (token) category = string(token);

                        token = strtok(nullptr, ",");
                        if (token) cost = atof(token);

                        token = strtok(nullptr, ",");
                        if (token) is_recurring = (strcmp(token, "Recurring") == 0);

                        token = strtok(nullptr, ",");
                        if (token) closing_date = string(token);
                        
                        new_interaction = new Contract(interaction_id, date, client_id, category, cost, is_recurring, closing_date);
                    }

                    if (new_interaction) {
                        client->add_interaction(new_interaction);
                        // cout << "\nInterazione caricata per Cliente ID " << client_id << " con ID Interazione " << interaction_id << "";
                    }
                }
            }

            fclose(file);
            //aggiorna i contatori per evitare ID interazioni errati
            Client::client_counter = clients.empty() ? 0 : clients.back()->get_client_ID();
            Interaction::interaction_counter = max_interaction_id;
            cout << "\nDati caricati correttamente. Numero totale di clienti: " << clients.size() << "\n";
        }
        


    //----------------- Salvare i dati sul file CRM.csv -------------------
        
        void save_crm(){
            file = fopen(percorso_al_file, "w");
            if (file == nullptr) {
                cout << "\nErrore nel salvataggio del file " << percorso_al_file << ". Verificare permessi di scrittura." << endl;
                return;
            }

            //scriviamo header sul file
            fprintf(file, "ID Cliente,Nome,Cognome,Email,ID Interazione,Data Interazione,Stato Interazione,Tipo Interazione,Ora Appuntamento,Luogo Appuntamento,Note Appuntamento,Categoria Contratto,Valore Complessivo Contratto,Metodo Pagamento Contratto,Data Chiusura Contratto\n"); 

            //per ogni cliente nella lista clients
            for (const auto& client : clients) {
                if (client == nullptr) continue; //evita problemi con allocazione della memoria
                
                //se cliente non ha interazioni scrive solo dati cliente
                if (client->get_interactions().empty()) {
                    fprintf(file, "%d,%s,%s,%s,,,,,,,,,,,\n",
                        client->get_client_ID(),
                        client->get_name().c_str(),
                        client->get_surname().c_str(),
                        client->get_email().c_str()
                    );
                } else {
                    //se cliente ha interazioni scrive una riga per ogni interazione del cliente
                    for (const auto& interaction : client->get_interactions()) {
                        if (Appointment* appointment = dynamic_cast<Appointment*>(interaction)) {
                            fprintf(file, "%d,%s,%s,%s,%d,%s,%s,Appuntamento,%s,%s,%s,,,,\n",
                                client->get_client_ID(),
                                client->get_name().c_str(),
                                client->get_surname().c_str(),
                                client->get_email().c_str(),
                                appointment->get_interaction_ID(),
                                appointment->get_date().c_str(),
                                appointment->get_is_completed() ? "Completed" : "Not Completed",
                                appointment->get_time().c_str(),
                                appointment->get_place().c_str(),
                                appointment->get_info().c_str()
                            );
                        } else if (Contract* contract = dynamic_cast<Contract*>(interaction)) {
                            fprintf(file, "%d,%s,%s,%s,%d,%s,%s,Contratto,,,,%s,%.2f euro,%s,%s\n",
                                client->get_client_ID(),
                                client->get_name().c_str(),
                                client->get_surname().c_str(),
                                client->get_email().c_str(),
                                contract->get_interaction_ID(),
                                contract->get_date().c_str(),
                                contract->get_is_completed() ? "Completed" : "Not Completed",
                                contract->get_contract_category().c_str(),
                                contract->get_total_cost(),
                                contract->get_is_recurring() ? "Recurring" : "One-shot",
                                contract->get_closing_date().c_str()
                            );
                        }
                    }
                }
            }

            fclose(file);

            cout << "\nCRM salvato con successo." << endl;
        }



    //----------------- 1 - Aggiungere un nuovo cliente -------------------

        void add_client(){
            string name, surname, email;
            bool valid_client = false;

            do{
                //input dei dati sul nuovo cliente
                cout << "Inserisci il nome del nuovo cliente: " << endl;
                getline(cin >> ws, name);

                //verifica se nome non è vuoto, normalizzazione in title case del primo char, in lower case degli altri char
                if (!name.empty()){
                    name[0] = toupper(name[0]);
                    for (int i = 1; i < name.length(); i++){
                        name[i] = tolower(name[i]);
                    } 
                }
                else{
                    cout << "\nNessun nome inserito. Riprovare." << endl;
                    continue; //torna all'inizio del ciclo
                }

                cout << "Inserisci il cognome del nuovo cliente: " << endl;
                getline(cin >> ws, surname);
                
                //verifica se cognome non è vuoto, normalizzazione in title case del primo char, in lower case degli altri char
                if (!surname.empty()){
                    surname[0] = toupper(surname[0]);
                    for (int i = 1; i < surname.length(); i++){
                        surname[i] = tolower(surname[i]);
                    } 
                }
                else{
                    cout << "\nNessun cognome inserito. Riprovare." << endl;
                    continue; //torna all'inizio del ciclo
                }

                cout << "Inserisci l'email del nuovo cliente: " << endl;
                getline(cin >> ws, email);

                //verifica se email non è vuota
                if (email.empty()) {
                    cout << "\nNessuna email inserita. Riprovare." << endl;
                    continue;//torna all'inizio del ciclo
                }


                //verifica se il cliente esiste già nel CRM
                //per ogni cliente presente nella list clients
                bool existing_client = false;
                for (const auto& client : clients) {
                    if (client == nullptr) continue; //evita problemi con allocazione della memoria
                    //se trova corrispondenza di nome E cognome 
                    if (client->get_name() == name && client->get_surname() == surname) {
                        cout << "\nUn cliente con lo stesso nome e cognome è già presente nel sistema. Inserire nuovamente i dati del cliente." << endl;
                        existing_client = true;
                        break;
                    }
                }

                if (!existing_client){
                    valid_client = true; //esce dal ciclo
                }

            }while(!valid_client);
                
            
            //aggiunta cliente usando puntatore a oggetto di tipo Client
            //new per allocare dinamicamente memoria per nuovo oggetto Client
            Client* added_client = new Client(name, surname, email); //ID viene gestito dal contatore statico della classe Client
            if (added_client == nullptr) {
                cout << "\nErrore: impossibile allocare memoria per il nuovo cliente." << endl;
                return;
            }
            
            clients.push_back(added_client); //aggiunto cliente a list clients

            //salvataggio su file CSV
            save_crm();
            
            cout << "\nCliente aggiunto con successo." << endl;
            cout << "ID assegnato: " << added_client->get_client_ID() << endl;

        }



    //----------------- 2 - Visualizzare tutti i clienti -------------------

        void show_clients() {
            //se list clients è vuota restituisce messaggio
            if (clients.empty()) {
                cout << "\nNessun cliente presente nel sistema." << endl;
                return;
            }

            cout << "\n=== ELENCO CLIENTI CRM ===\n" << endl;
            
            for (const auto& client : clients) {
                if (client == nullptr) continue; //evita problemi con allocazione della memoria
                client->visualizza();
                cout << "--------------------------------\n";
            }

            cout << "\nNumero totale di clienti nel sistema: " << clients.size() << endl;
        }


    //----------------- 3 - Modifica un cliente -------------------
        void modify_client(){

        //se list clients è vuota restituisce messaggio
        if (clients.empty()) {
            cout << "\nNessun cliente presente nel sistema." << endl;
            return;
        }

        while(true){
            //input inserito dal cliente
            string search_partofname;
            //scelta modalità di ricerca (nome o cognome)
            int choice;
                
            do{
                cout << "\nCercare il cliente da modificare per:\n1 - Nome\n2 - Cognome\nDigita il numero corrispondente alla scelta: ";
                cin >> choice;

                if (choice != 1 && choice != 2) {
                    cout << "Scelta non valida. Inserisci 1 per nome o 2 per cognome:\n";
                }
            } while (choice != 1 && choice != 2);

                
            cout << "Inserisci il termine di ricerca: ";
            getline(cin >> ws, search_partofname);
                
            //normalizza il termine di ricerca, prima lettera maiuscola resto minuscolo
            search_partofname[0] = toupper(search_partofname[0]);
            for (int i = 1; i < search_partofname.length(); i++) {
                search_partofname[i] = tolower(search_partofname[i]);
            }
                
            //verifica se almeno un cliente viene trovato
            bool found = false;
            Client* client_to_modify = nullptr; //puntatore per cliente da modificare
                
            cout << "\nRisultati della ricerca:\n" << endl;
                
            //ricerca per ogni cliente in list clients
            for (const auto& client : clients) {
                if (client == nullptr) continue; //evita problemi con allocazione della memoria
                //corrispondenza tra nome o cognome e il termine di ricerca dell'utente
                bool match = (choice == 1 && client->get_name() == search_partofname) ||
                             (choice == 2 && client->get_surname() == search_partofname);
                    
                //se c'è corrispondenza, stampate info del cliente
                if (match) {
                    client_to_modify = client;
                    client->visualizza();
                    cout << "--------------------------------\n";
                    found = true;
                    break;
                }
            }
                
            //se nessun cliente corrisponde alla ricerca
            if (!found) {
                cout << "Nessun cliente trovato con questo criterio di ricerca. Riprovare." << endl;
                continue;
            }

            string modified_name, modified_surname, modified_email;
            cout << "Inserisci il nuovo nome (vuoto per mantenere invariato): ";
            getline(cin, modified_name);
            //se il nome rimane vuoto, non modificare
            if (!modified_name.empty()) {
                modified_name[0] = toupper(modified_name[0]);
                for (int i = 1; i < modified_name.length(); i++) {
                    modified_name[i] = tolower(modified_name[i]);
                }
                client_to_modify->set_name(modified_name);
            }

            cout << "Inserisci il nuovo cognome (vuoto per mantenere invariato): ";
            getline(cin, modified_surname);
            //se il cognome rimane vuoto, non modificare
            if (!modified_surname.empty()) {
                modified_surname[0] = toupper(modified_surname[0]);
                for (int i = 1; i < modified_surname.length(); i++) {
                        modified_surname[i] = tolower(modified_surname[i]);
                }
                client_to_modify->set_surname(modified_surname);
            }

            cout << "Inserisci la nuova email (vuoto per mantenere invariato): ";
            getline(cin, modified_email);
            //se l'email rimane vuota, non modificare
            if (!modified_email.empty()) {
                client_to_modify->set_email(modified_email);
            }
                
            //salva le modifiche sul file
            save_crm();
                
            cout << "\nCliente modificato con successo." << endl;
            return;
    
        }
    }

    //----------------- 4 - Eliminare un cliente -------------------
        void delete_client(){

            //se list clients è vuota restituisce messaggio
            if (clients.empty()) {
                cout << "\nNessun cliente presente nel sistema." << endl;
                return;
            }

            while(true){
                //input inserito dal cliente
                string search_partofname;
                //scelta modalità di ricerca (nome o cognome)
                int choice;
                
                do{
                    cout << "\nCercare il cliente da eliminare per:\n1 - Nome\n2 - Cognome\nDigita il numero corrispondente alla scelta: ";
                    cin >> choice;

                    if (choice != 1 && choice != 2) {
                        cout << "Scelta non valida. Inserisci 1 per nome o 2 per cognome:\n";
                    }
                } while (choice != 1 && choice != 2);

                
                cout << "Inserisci il termine di ricerca: ";
                getline(cin >> ws, search_partofname);
                
                //normalizza il termine di ricerca, prima lettera maiuscola resto minuscolo
                search_partofname[0] = toupper(search_partofname[0]);
                for (int i = 1; i < search_partofname.length(); i++) {
                    search_partofname[i] = tolower(search_partofname[i]);
                }
                
                //verifica se almeno un cliente viene trovato
                bool found = false;
                int found_counter = 0;
                Client* client_to_delete = nullptr; //puntatore per cliente da eliminare
                
                cout << "\nRisultati della ricerca:\n" << endl;
                
                //ricerca per ogni cliente in list clients
                for (const auto& client : clients) {
                    if (client == nullptr) continue; //evita problemi con allocazione della memoria
                    //corrispondenza tra nome o cognome e il termine di ricerca dell'utente
                    bool match = (choice == 1 && client->get_name() == search_partofname) ||
                                 (choice == 2 && client->get_surname() == search_partofname);
                    
                    //se c'è corrispondenza, stampate info del cliente
                    if (match) {
                        found_counter++;
                        cout << "Cliente #" << found_counter << ":" << endl;
                        client->visualizza();
                        cout << "--------------------------------\n";
                        found = true;
                        if (found_counter == 1) {
                            client_to_delete = client;
                        }
                    }
                }
                
                //se nessun cliente corrisponde alla ricerca
                if (!found) {
                    cout << "Nessun cliente trovato con questo criterio di ricerca." << endl;
                    continue;
                }

                //se viene trovato più di un cliente chiede quale eliminare
                int client_number = 1;
                if (found_counter > 1) {
                    do {
                        cout << "\nInserisci il numero del cliente da eliminare (1-" << found_counter << "): ";
                        cin >> client_number;
                        if (client_number < 1 || client_number > found_counter) {
                            cout << "Scelta non valida." << endl;
                        }
                    } while (client_number < 1 || client_number > found_counter);

                    //cerca il cliente selezionato
                    found_counter = 0;
                    for (const auto& client : clients) {
                        if (client == nullptr) continue; //evita problemi con allocazione della memoria
                        bool match = (choice == 1 && client->get_name() == search_partofname) ||
                                     (choice == 2 && client->get_surname() == search_partofname);
                        if (match) {
                            found_counter++;
                            if (found_counter == client_number) {
                                client_to_delete = client;
                                break;
                            }
                        }
                    }
                }

                //rimuove il cliente dalla lista clients
                clients.remove(client_to_delete);
                delete client_to_delete;
                
                //salva le modifiche sul file
                save_crm();
                
                cout << "\nCliente eliminato con successo." << endl;
                return;
            }    
        } 
    

    //----------------- 5 - Cercare un cliente per nome o cognome -------------------
        void search_client() {

            //se list clients è vuota restituisce messaggio
            if (clients.empty()) {
                cout << "\nNessun cliente presente nel sistema." << endl;
                return;
            }

            //input inserito dal cliente
            string search_partofname;
            //scelta modalità di ricerca (nome o cognome)
            int choice;
                
            do{
                cout << "\nCercare il cliente per:\n1 - Nome\n2 - Cognome\nDigita il numero corrispondente alla scelta: ";
                cin >> choice;

                if (choice != 1 && choice != 2) {
                    cout << "Scelta non valida. Inserisci 1 per nome o 2 per cognome:\n";
                }
            } while (choice != 1 && choice != 2);
   
            cout << "Inserisci il termine di ricerca: ";
            getline(cin >> ws, search_partofname);
                
            //normalizza il termine di ricerca, prima lettera maiuscola resto minuscolo
            search_partofname[0] = toupper(search_partofname[0]);
            for (int i = 1; i < search_partofname.length(); i++) {
                search_partofname[i] = tolower(search_partofname[i]);
            }
                
            //verifica se almeno un cliente viene trovato
            bool found = false;
            int found_counter = 0;
                
            cout << "\nRisultati della ricerca:\n" << endl;
                
            //ricerca per ogni cliente in list clients
            for (const auto& client : clients) {
                if (client == nullptr) continue; //evita problemi con allocazione della memoria
                //corrispondenza tra nome o cognome e il termine di ricerca dell'utente
                bool match = (choice == 1 && client->get_name() == search_partofname) ||
                            (choice == 2 && client->get_surname() == search_partofname);
                    
                //se c'è corrispondenza, stampate info del cliente
                if (match) {
                    cout << "Cliente #" << found_counter + 1 << ":" << endl;
                    client->visualizza();
                    cout << "--------------------------------\n";
                    found = true;
                    found_counter++;
                }
            }
                
            //se nessun cliente corrisponde alla ricerca
            if (!found) {
                cout << "Nessun cliente trovato con questo criterio di ricerca." << endl;
            }
            else {
                cout << "\nNumero di clienti trovati con il termine di ricerca: " << found_counter << endl;
                }
        
        }


    //----------------- 6 - Aggiungere un'interazione con InsuraPro Solutions -------------------
        void add_interaction() {
            //se list clients è vuota restituisce messaggio
            if (clients.empty()) {
                cout << "\nNessun cliente presente nel sistema. Impossibile aggiungere interazioni." << endl;
                return;
            }

            while(true){
                //input inserito dal cliente
                string search_partofname;
                //scelta modalità di ricerca (nome o cognome)
                int choice;
                
                do{
                    cout << "\nCercare il cliente a cui aggiungere un'interazione per:\n1 - Nome\n2 - Cognome\nDigita il numero corrispondente alla scelta: ";
                    cin >> choice;

                    if (choice != 1 && choice != 2) {
                        cout << "Scelta non valida. Inserisci 1 per nome o 2 per cognome:\n";
                    }
                } while (choice != 1 && choice != 2);

                cout << "Inserisci il termine di ricerca: ";
                getline(cin >> ws, search_partofname);
                
                //normalizza il termine di ricerca, prima lettera maiuscola resto minuscolo
                search_partofname[0] = toupper(search_partofname[0]);
                for (int i = 1; i < search_partofname.length(); i++) {
                    search_partofname[i] = tolower(search_partofname[i]);
                }

                //verifica se almeno un cliente viene trovato
                bool found = false;
                int found_counter = 0;
                Client* found_client = nullptr; //puntatore per cliente a cui aggiungere interazione
                
                cout << "\nRisultati della ricerca:\n" << endl;
                
                //ricerca per ogni cliente in list clients
                for (const auto& client : clients) {
                    if (client == nullptr) continue; //evita problemi con allocazione della memoria
                    //corrispondenza tra nome o cognome e il termine di ricerca dell'utente
                    bool match = (choice == 1 && client->get_name() == search_partofname) ||
                                 (choice == 2 && client->get_surname() == search_partofname);
                    
                    //se c'è corrispondenza, stampate info del cliente
                    if (match) {
                        found_counter++;
                        found_client = client;
                        cout << "Cliente #" << found_counter << ":" << endl;
                        client->visualizza();
                        cout << "--------------------------------\n";
                        found = true;
                    }
                }
                
                //se nessun cliente corrisponde alla ricerca
                if (!found) {
                    cout << "Nessun cliente trovato con questo criterio di ricerca." << endl;
                    continue;
                }
                
                //se viene trovato più di un cliente chiede a quale aggiungere l'interazione
                int client_number = 1;
                if (found_counter > 1) {
                    do {
                        cout << "\nInserisci il numero del cliente a cui aggiungere l'interazione (1-" << found_counter << "): ";
                        cin >> client_number;
                        if (client_number < 1 || client_number > found_counter) {
                            cout << "Scelta non valida." << endl;
                        }
                    } while (client_number < 1 || client_number > found_counter);

                    //cerca il cliente selezionato
                    found_counter = 0;
                    for (const auto& client : clients) {
                        if (client == nullptr) continue; //evita problemi con allocazione della memoria
                        bool match = (choice == 1 && client->get_name() == search_partofname) ||
                                     (choice == 2 && client->get_surname() == search_partofname);
                        if (match) {
                            found_counter++;
                            if (found_counter == client_number) {
                                found_client = client;
                                break;
                            }
                        }
                    }
                }

                //scelta del tipo di interazione
                int interaction_type;
                do{
                    cout << "\nScegliere il tipo di interazione:\n1 - Appuntamento\n2 - Contratto\nDigita il numero corrispondente: ";
                    cin >> interaction_type;

                    if (interaction_type != 1 && interaction_type != 2) {
                        cout << "Scelta non valida. Inserisci 1 per Appuntamento o 2 per Contratto.\n";
                    }
                } while (interaction_type != 1 && interaction_type != 2);

                //input per l'interazione
                string date;
                bool is_completed;

                cout << "Inserisci la data dell'interazione (DD-MM-YYYY): ";
                getline(cin >> ws, date);

                //normalizza data
                string normalized_date = normalize_date(date);
                if (normalized_date.empty()) {
                    cout << "Data non valida. Riprovare." << endl;
                    return;
                }

                cout << "L'interazione è stata completata? (1 - Si, 0 - No): ";
                cin >> is_completed;

                //creazione dell'interazione in base al tipo scelto
                if (interaction_type == 1) {
                    //appuntamento
                    string time, place, info;
                    
                    cout << "Inserisci l'ora dell'appuntamento (HH:MM): ";
                    getline(cin >> ws, time);
                    
                    cout << "Inserisci il luogo dell'appuntamento: ";
                    getline(cin >> ws, place);
                    
                    cout << "Inserisci informazioni aggiuntive: ";
                    getline(cin >> ws, info);

                    Appointment* new_appointment = new Appointment(normalized_date, found_client->get_client_ID(), place, time, info, is_completed);
                    found_client->add_interaction(new_appointment);
                }
                else if (interaction_type == 2) {
                    //contratto
                    string category, closing_date;
                    float total_cost;
                    bool is_recurring;

                    cout << "Inserisci la categoria del contratto: ";
                    getline(cin >> ws, category);

                    cout << "Inserisci il valore complessivo del contratto: ";
                    cin >> total_cost;

                    cout << "Prevede un pagamento ricorrente? (1 - Sì, 0 - No): ";
                    cin >> is_recurring;

                    cout << "Inserisci la data di chiusura del contratto (DD-MM-YYYY): ";
                    getline(cin >> ws, closing_date);

                    // Normalizza anche la data di chiusura
                    string normalized_closing_date = normalize_date(closing_date);
                    if (normalized_closing_date.empty()) {
                        cout << "Data di chiusura non valida. Riprovare." << endl;
                        return;
                    }

                    Contract* new_contract = new Contract(normalized_date, found_client->get_client_ID(), category, total_cost, is_recurring, normalized_closing_date);
                    found_client->add_interaction(new_contract);
                }
                else {
                    cout << "Tipo di interazione non valido." << endl;
                    return;
                }

                //salva delle modifiche
                save_crm();
                
                cout << "\nInterazione aggiunta con successo." << endl;
                return;
            }

        }


    //----------------- 7 - Visualizzare tutte le interazioni con InsuraPro Solutions -------------------
        void show_interactions() {

            //se list clients è vuota restituisce messaggio
            if (clients.empty()) {
                cout << "\nNessun cliente presente nel sistema." << endl;
                return;
            }

            cout << "\n=== ELENCO INTERAZIONI CRM ===\n" << endl;
            
            //contatore per interazioni
            int total_interactions = 0;
    
            //per ogni cliente in list clients
            for (const auto& client : clients) {
                if (client == nullptr) continue; //evita problemi con allocazione della memoria
        
                //se il cliente non ha interazioni, salta al prossimo cliente
                if (client->get_interactions().empty()) {
                    continue;
                }
        
                //stampa intestazione cliente
                cout << "Cliente: " << client->get_name() << " " << client->get_surname() << " (ID: " << client->get_client_ID() << ")" << endl;
                cout << "--------------------------------\n";
        
                //per ogni interazione del cliente
                for (const auto& interaction : client->get_interactions()) {
                    if (interaction == nullptr) continue;
            
                    interaction->visualizza();
                    interaction->interaction_type();
                    cout << "--------------------------------\n";
                    total_interactions++;
                }
            }

            if (total_interactions == 0) {
                cout << "Nessuna interazione presente nel sistema." << endl;
            } else {
                cout << "\nNumero totale di interazioni nel sistema: " << total_interactions << endl;
            }
        } 



    //----------------- 8 - Cercare un'interazione con InsuraPro Solutions -------------------

        void search_interaction(){

            //se list clients è vuota restituisce messaggio
            if (clients.empty()) {
                cout << "\nNessun cliente presente nel sistema." << endl;
                return;
            }

            int choice;
            do {
                cout << "\nCercare l'interazione per:\n1 - Data\n2 - Tipo (Appuntamento/Contratto)\nDigita il numero corrispondente alla scelta: ";
                cin >> choice;

                if (choice != 1 && choice != 2) {
                    cout << "Scelta non valida. Inserisci 1 per data o 2 per tipo:\n";
                }
            } while (choice != 1 && choice != 2);

            if (choice == 1) {
                //ricerca per data
                string search_date;
                cout << "Inserisci la data da cercare (DD-MM-YYYY): ";
                getline(cin >> ws, search_date);

                //normalizza data
                string normalized_date = normalize_date(search_date);
                if (normalized_date.empty()) {
                    cout << "Data non valida. Riprovare." << endl;
                    return;
                }
        
                bool found = false;
                int found_counter = 0;
        
                cout << "\nRisultati della ricerca:\n" << endl;

                //per ogni cliente
                for (const auto& client : clients) {
                    if (client == nullptr) continue;

                    //per ogni interazione del cliente
                    for (const auto& interaction : client->get_interactions()) {
                        if (interaction == nullptr) continue;

                        //se la data corrisponde
                        if (interaction->get_date() == normalized_date) {
                            cout << "Cliente: " << client->get_name() << " " << client->get_surname() << endl;
                            interaction->visualizza();
                            interaction->interaction_type();
                            cout << "--------------------------------\n";
                            found = true;
                            found_counter++;
                        }
                    }
                }

                if (!found) {
                    cout << "Nessuna interazione trovata per la data specificata." << endl;
                } else {
                    cout << "\nNumero di interazioni trovate: " << found_counter << endl;
                }
        
            } else {
                //ricerca per tipo
                int type_choice;
                do {
                    cout << "\nTipo di interazione da cercare:\n1 - Appuntamento\n2 - Contratto\nDigita il numero corrispondente: ";
                    cin >> type_choice;

                    if (type_choice != 1 && type_choice != 2) {
                        cout << "Scelta non valida. Inserisci 1 per Appuntamento o 2 per Contratto.\n";
                    }
                } while (type_choice != 1 && type_choice != 2);

                bool found = false;
                int found_counter = 0;

                cout << "\nRisultati della ricerca:\n" << endl;

                //per ogni cliente
                for (const auto& client : clients) {
                    if (client == nullptr) continue;

                    //per ogni interazione del cliente
                    for (const auto& interaction : client->get_interactions()) {
                        if (interaction == nullptr) continue;

                        //controlla il tipo di interazione usando dynamic_cast
                        if (type_choice == 1 && dynamic_cast<Appointment*>(interaction)) {
                            cout << "Cliente: " << client->get_name() << " " << client->get_surname() << endl;
                            interaction->visualizza();
                            interaction->interaction_type();
                            cout << "--------------------------------\n";
                            found = true;
                            found_counter++;
                        } else if (type_choice == 2 && dynamic_cast<Contract*>(interaction)) {
                            cout << "Cliente: " << client->get_name() << " " << client->get_surname() << endl;
                            interaction->visualizza();
                            interaction->interaction_type();
                            cout << "--------------------------------\n";
                            found = true;
                            found_counter++;
                        }
                    }
                }
        
                if (!found) {
                    cout << "Nessuna interazione trovata del tipo specificato." << endl;
                } else {
                    cout << "\nNumero di interazioni trovate: " << found_counter << endl;
                }
            }
        }

        

        //distruttore di CRM che chiude anche il file
        ~CRM() {
            save_crm(); //salva i dati prima di distruggere memoria
           
            //deallocata memoria per clienti e interazioni
            for (auto& client : clients) {
                for (auto& interaction : client->get_interactions()) {
                    delete interaction;
                }
                delete client;
            }
        }
};


int main(){

    CRM crm;
    int cases;
   
    while (true){

        int operation;

        cout << "\n======= OPERAZIONI DISPONIBILI SUL CRM =======\n" << endl; 
        cout << "\n1 - Aggiungi Cliente\n2 - Visualizza Clienti\n3 - Modifica Cliente\n4 - Elimina Cliente\n5 - Ricerca Cliente\n6 - Aggiungi Interazione con InsuraPro Solutions\n7 - Visualizza Interazioni con InsuraPro Solutions\n8 - Ricerca Interazione con InsuraPro Solutions\n9 - Esci" << endl; 
        cout << "\nDigita il numero corrispondente all'operazione desiderata: " << endl;
        cin >> operation;

        switch (operation) {
            case 1: crm.add_client(); break;
            case 2: crm.show_clients(); break;
            case 3: crm.modify_client(); break;
            case 4: crm.delete_client(); break;
            case 5: crm.search_client(); break;
            case 6: crm.add_interaction(); break;
            case 7: crm.show_interactions(); break;
            case 8: crm.search_interaction(); break;
            case 9: return 0;
            default: cout << "Scelta non valida!\n";
        }
    }
}
