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


