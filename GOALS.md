[cite_start]Level 1, tamamen işletim sistemiyle (OS) doğrudan iletişim kurmaya dayalı **"Unix Sistem Programlama"** dünyasıdır[cite: 8, 9, 10]. Bu bölümü sindirerek öğrenmek, ileride kendi kabuğunu (shell) veya sistem araçlarını yazman için temel oluşturur.

İşte Level 1 odaklı GitHub repo ismi önerileri ve her bir soru için odaklanman gereken öğrenme hedefleri:

## 📂 Level 1 GitHub Repo İsim Önerileri
Sadece bu seviyeye odaklanacaksan şu isimleri kullanabilirsin:
* `42-Rank04-System-Calls`
* `Unix-Process-Management-42`
* `42-Level1-Systems-Basics`
* `IPC-and-Process-Control-Rank04`

---

## 🛠 Seviye 1: Sorular ve Öğrenme Hedefleri

Level 1'deki soruları sırasıyla çözerek şu yetkinlikleri kazanmayı amaçlamalısın:

### 1. ft_popen (Pipe & Redirection)
[cite_start]**Amacı:** İki farklı süreç arasında tek yönlü bir veri yolu (pipe) kurmayı öğretmektir[cite: 1, 11].
* [cite_start]**Ne öğreneceksin?** `pipe()` fonksiyonuyla veri tüneli açmayı ve `dup2()` ile standart çıktı/girdiyi (STDOUT/STDIN) bu tünele yönlendirmeyi[cite: 3, 11, 13].
* [cite_start]**Kritik nokta:** Kullanılmayan pipe uçlarını `close()` ile kapatmazsan programın sonsuza kadar bekleyebilir (hanging)[cite: 14, 30].


### 2. picoshell (Multi-Process Pipelines)
[cite_start]**Amacı:** Birden fazla komutun (örneğin `ls | grep a | wc -l`) aynı anda ve birbirine bağlı çalışmasını yönetmektir[cite: 2, 15].
* [cite_start]**Ne öğreneceksin?** Bir döngü içinde birden fazla `fork()` yaparak süreçler oluşturmayı ve her birinin çıktısını bir sonrakine hatasız aktarmayı[cite: 16, 17, 39].
* [cite_start]**Kritik nokta:** Her çocuk sürecin (`child process`) bir önceki komutun okuma ucunu devralması gerekir[cite: 17].

### 3. sandbox (Process Monitoring & Signals)
[cite_start]**Amacı:** Bir programın dışarıdan bir "gözlemci" (supervisor) gibi nasıl denetlendiğini öğretmektir[cite: 3, 18].
* [cite_start]**Ne öğreneceksin?** `alarm()` ile zaman aşımı (timeout) kurmayı ve `waitpid()` status makrolarını (`WIFEXITED`, `WIFSIGNALED`) kullanarak sürecin normal mi bittiğini yoksa segfault mı aldığını analiz etmeyi[cite: 4, 19, 20].
* [cite_start]**Kritik nokta:** `sigaction` veya sinyal yakalayıcılarla sürecin çalışma sağlığını kontrol etmek[cite: 4, 54].


---

[cite_start]Bu üç soruyu bitirdiğinde, işletim sisteminin süreçleri nasıl yönettiğini, veriyi bir yerden bir yere nasıl taşıdığını ve hataları nasıl raporladığını somut olarak kavramış olacaksın[cite: 32, 52]. Bu temel, Level 2'deki karmaşık veri yapılarına (AST) geçtiğinde sistem tarafında kafa karışıklığı yaşamamanı sağlar.

İlk olarak hangi sorudan başlamayı planlıyorsun?


















Evet, tam olarak öyle! [cite_start]**Exam Rank 04'ün Level 1 kısmı %100 "Unix Sistem Programlama" (Unix System Programming) konusuna odaklanır.** [cite: 69]

[cite_start]Sadece kodun iç mantığıyla değil, kodun işletim sistemiyle nasıl konuştuğuyla ilgilenirsin. [cite: 33] Bu süreci daha iyi anlaman için temel bileşenleri şöyle özetleyebiliriz:

### 🛠 Unix Sistem Programlama Nedir? (Level 1 Odaklı)

[cite_start]Unix sistem programlama, bir programcının işletim sistemi çekirdeği (kernel) ile doğrudan iletişim kurmak için **Sistem Çağrılarını (System Calls)** kullanmasıdır. [cite: 52] Sınavdaki üç soru da bu iletişimin farklı yönlerini öğretir:

* [cite_start]**Süreç Yönetimi (Process Management):** `fork()` kullanarak yeni süreçler oluşturmak ve bu süreçlerin yaşam döngüsünü (başlatma, bekletme, sonlandırma) yönetmek. [cite: 12, 39, 55]
* [cite_start]**Süreçler Arası İletişim (IPC - Inter-Process Communication):** `pipe()` kullanarak, birbirinden bağımsız çalışan iki program arasında bir "veri tüneli" kurmak. [cite: 10, 53]
* [cite_start]**Girdi/Çıktı Yönlendirme (I/O Redirection):** `dup2()` kullanarak bir programın ekran yerine bir dosyaya veya bir pipe'a yazmasını sağlamak. [cite: 11, 13]
* [cite_start]**Sinyal Yönetimi (Signals):** `alarm()` veya `sigaction()` ile çalışan bir sürece dışarıdan müdahale etmek (örneğin: "Çok uzun sürdün, artık dur!") veya onun neden çöktüğünü (Segfault vb.) anlamak. [cite: 4, 19, 20, 54]


### 💡 Neden Bunu Öğreniyorsun?

[cite_start]42'de bu aşamaya gelmenin sebebi, yazdığın kodun "kara kutu" içinde nasıl çalıştığını anlamanı sağlamaktır. [cite: 45]
1.  [cite_start]**ft_popen** ile sistemin komutları nasıl arka arkaya bağladığını öğrenirsin. [cite: 72]
2.  [cite_start]**picoshell** ile aslında bir terminalin (bash/zsh gibi) temel çalışma mantığını inşa edersin. [cite: 15, 75]
3.  [cite_start]**sandbox** ile sistem kaynaklarını denetleyen korumalı alanların mantığını kavrarsın. [cite: 18, 78]

Özetle; [cite_start]Rank 02 ve 03'te **"Nasıl bir algoritma kurarım?"** sorusuna yanıt ararken, Rank 04 Level 1'de **"İşletim sistemine bu işi nasıl yaptırırım?"** sorusuna yanıt veriyorsun. [cite: 47, 48, 65]

Sence bu "sistemle konuşma" mevzusu, saf algoritma yazmaktan daha mı heyecan verici yoksa daha mı ürkütücü?
























Exam Rank 04, senin yazılım dünyasındaki konumunu "kod yazan kişi"den **"sistem mimarı"** seviyesine taşımayı hedefler. Rank 02 ve 03 daha çok algoritmik düşünceye odaklanırken, bu aşama bilgisayarın mutfağıyla ilgilidir.

GitHub repon için isim önerileri ve seviyelerin tam olarak neyi "öğretmeyi" amaçladığına dair bir döküm aşağıdadır:

---

## 📂 GitHub Repo İsim Önerileri
Reponun ismi hem profesyonel hem de içeriği tanımlayıcı olmalı:
* `42-Exam-Rank-04` (Klasik ve net)
* `Unix-Systems-and-Parsing` (İçeriğe vurgu yapar)
* `42-Sys-and-AST` (System calls ve Abstract Syntax Tree odaklı)
* `From-Shell-to-Compiler` (Gelişim sürecini anlatır)

---

## 🎯 Seviyelerin Amacı: Neyi Öğreniyorsun?

Rank 02 ve 03'teki algoritma ve backtracking odaklı yapının aksine, burada odak **Sistem Programlama** ve **Dil İşleme** üzerine kayar:

### **Level 1: System-Level Programming (Sistem Seviyesi Programlama)**
[cite_start]**Neyi amaçlıyor?** İşletim sistemi kaynaklarını (process, pipe, signal) yönetmeyi öğrenmeni. [cite: 1, 10]
* [cite_start]**ft_popen & picoshell:** Bir programın diğeriyle nasıl konuştuğunu (Inter-Process Communication - IPC) ve verinin boru hatları (pipes) üzerinden nasıl aktığını anlamanı sağlar. [cite: 10, 15]
* [cite_start]**sandbox:** İşletim sisteminin bir süreci nasıl denetlediğini, çökmeleri (segfault) veya sonsuz döngüleri (timeout) nasıl sinyallerle yakaladığını öğretir. [cite: 3, 18]
* [cite_start]**Kilit Kavramlar:** `fork()`, `pipe()`, `dup2()`, `waitpid()` ve sinyal yönetimi. [cite: 3, 4]


### **Level 2: Abstract Structures & Formal Languages (Soyut Yapılar ve Biçimsel Diller)**
[cite_start]**Neyi amaçlıyor?** Veriyi anlamlandırmayı ve bir dilden başka bir dile (veya yapıya) dönüştürmeyi öğrenmeni. [cite: 21, 41]
* [cite_start]**argo (JSON Parser):** Düz bir metin yığınını (string), bilgisayarın kolayca işleyebileceği hiyerarşik bir ağaç yapısına (**AST - Abstract Syntax Tree**) dönüştürme yeteneğini sınar. [cite: 4, 22, 43]
* [cite_start]**vbc (Compiler):** Bir dilde yazılmış ifadeyi (matematiksel işlem), başka bir dilin mantığına (stack-based assembly) çevirmeyi, yani derleyici mantığının temelini öğretir. [cite: 25, 27]
* [cite_start]**Kilit Kavramlar:** Recursive Descent Parsing (Özyinelemeli İnişli Ayrıştırma), Tokenization ve AST inşası. [cite: 5, 7, 22]


---

## 🛠 Özet Karşılaştırma

| Sınav | Temel Odak Noktası | Amaçlanan Yetkinlik |
| :--- | :--- | :--- |
| **Rank 02** | Temel Algoritmalar | Kodlama mantığı ve döngüler. |
| **Rank 03** | Backtracking / Rekürsiyon | Karmaşık olasılıkları yönetme. |
| **Rank 04** | **System & Parsing** | [cite_start]**OS kaynak yönetimi ve veri modelleme.** [cite: 32, 45] |

[cite_start]Bu seviyeyi tamamladığında, sadece bir problem çözen değil, bir kabuk (shell) tasarlayabilen veya basit bir veri formatını (JSON) yorumlayabilen bir mühendis olma yolunda büyük bir adım atmış olacaksın. [cite: 45]

Sence sistem tarafı (Level 1) mı yoksa yapısal analiz tarafı (Level 2) mı kariyer hedeflerine daha yakın?


























[cite_start]**Exam Rank 04'ün Level 2 kısmı**, odağını işletim sisteminden çekip **"Dil İşleme ve Veri Modelleme"** (Language Processing & Data Modeling) alanına çevirir[cite: 21, 57]. [cite_start]Bu seviyede amaç, bilgisayarların karmaşık metinleri nasıl "anladığını" ve bunları nasıl "işlediğini" kavramandır[cite: 41, 58].

İşte Level 2 için öğrenme hedefleri ve proje detayları:

---

### 🎯 Level 2: Neyi Öğreniyorsun?

[cite_start]Bu seviye, bir yazılım mühendisinin en üst düzey yetkinliklerinden biri olan **"Ayrıştırma (Parsing)"** ve **"Derleme (Compilation)"** mantığını öğretir[cite: 42, 60].

#### 1. argo (JSON Parser)
* [cite_start]**Amacı:** Düz bir karakter dizisi (string) halindeki veriyi, programın içinde kolayca dolaşabileceğin hiyerarşik bir ağaç yapısına (**AST - Abstract Syntax Tree**) dönüştürmektir[cite: 4, 43, 59].
* [cite_start]**Ne öğreneceksin?** * **Recursive Descent Parsing:** Bir kuralın (örneğin bir JSON objesi) kendi içinde başka kuralları (diziler veya iç içe objeler) nasıl çağırdığını[cite: 22, 24].
    * [cite_start]**Veri Yapıları:** Dinamik olarak büyüyen ağaç yapılarını bellek sızıntısı olmadan yönetmeyi[cite: 28, 37].


#### 2. vbc (Very Basic Compiler)
* [cite_start]**Amacı:** Matematiksel bir ifadeyi (insan dili) alıp, işlemcinin yığın (stack) üzerinde adım adım çalıştırabileceği bir dizi komuta (makine mantığı) çevirmektir[cite: 25, 44, 60].
* **Ne öğreneceksin?**
    * [cite_start]**Tokenization:** Metni anlamlı parçalara (sayılar, operatörler, parantezler) ayırmayı[cite: 7, 61].
    * [cite_start]**İşlem Önceliği:** Çarpma ve bölme işlemlerinin toplama ve çıkarmadan önce yapılması gerektiğini kodun hiyerarşik yapısıyla çözmeyi[cite: 26, 27].
    * [cite_start]**Code Generation:** Analiz edilen veriden düşük seviyeli (assembly benzeri) talimatlar üretmeyi[cite: 6, 7].


---

### 📂 Level 2 İçin GitHub Repo İsim Önerileri
Eğer bu seviyeyi ayrı bir repoda tutmak veya ana reponda bir klasör yapmak istersen şu isimleri kullanabilirsin:
* `42-Rank04-Parsers-and-Compilers`
* `AST-Construction-and-Data-Modeling`
* `42-Recursive-Descent-Methods`
* `Language-Processing-Basics-42`

---

### 🛠 Özet Karşılaştırma

| Özellik | Level 1 (Unix System) | Level 2 (Parsing & Compilers) |
| :--- | :--- | :--- |
| **Odak** | [cite_start]İşletim Sistemi Kaynakları [cite: 52] | [cite_start]Veri Yapıları ve Mantıksal Analiz [cite: 58] |
| **Temel Araç** | [cite_start]Sistem Çağrıları (System Calls) [cite: 87] | [cite_start]Rekürsiyon ve AST [cite: 61] |
| **Hata Türü** | [cite_start]Pipe çökmesi veya Zombi süreç [cite: 14] | [cite_start]Sözdizimi hatası veya Bellek sızıntısı [cite: 29] |

[cite_start]**Özetle:** Level 2'yi bitirdiğinde, bir verinin veya bir kod satırının bilgisayar tarafından nasıl adım adım çözümlendiğini ve başka bir forma dönüştürüldüğünü öğrenmiş olacaksın[cite: 45, 66].

Level 1'deki "sistemle konuşma" kısmını hallettikten sonra, Level 2'deki bu "dil tasarlama" mantığı sence daha mı zorlayıcı görünüyor?
