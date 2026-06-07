# ⚙️ Unix System Programming

<div align="center">

![42 School](https://img.shields.io/badge/School-42-black?style=for-the-badge&logo=42)
![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Unix](https://img.shields.io/badge/Unix-System_Calls-orange?style=for-the-badge)
![Exercises](https://img.shields.io/badge/Exercises-3-success?style=for-the-badge)

**İşletim sistemiyle doğrudan konuş. Süreç yönet. Sinyalleri yakala.**

*`ft_popen`, `picoshell` ve `sandbox`.*

[Ne Öğreniyorsun?](#-ne-öğreniyorsun) • [Egzersizler](#-egzersizler) • [Kurulum](#-kurulum) • [Temel Kavramlar](#-temel-kavramlar)

</div>

---

## 🎯 Projenin Amacı

<img align="right" alt="Algorithm Animation" width="300" src="https://media3.giphy.com/media/v1.Y2lkPTc5MGI3NjExM29ha2xqaW1jM3k2bHFlZGIyZG1xMXhjYzZncjR3Z3Qxb2RjMW5vZiZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/bjC8sdurIYfElHXfxR/giphy.gif">

Bu bölüm tamamen **Unix Sistem Programlama** üzerinedir. Yazdığın kodun kara kutu içinde nasıl çalıştığını değil, kodun **işletim sistemiyle nasıl konuştuğunu** öğrenirsin. Her egzersiz bu iletişimin farklı bir boyutunu ele alır:

| Egzersiz | Konu | Kritik Sistem Çağrıları |
|----------|------|------------------------|
| `ft_popen` | Pipe & I/O Yönlendirme | `pipe`, `fork`, `dup2`, `execvp` |
| `picoshell` | Çoklu Süreç Pipeline | `fork`, `pipe`, `dup2`, `execvp`, `wait` |
| `sandbox` | Süreç Denetimi & Sinyaller | `fork`, `waitpid`, `alarm`, `sigaction`, `kill` |

---

## 🧠 Ne Öğreniyorsun?

### 🔀 Süreç Yönetimi (Process Management)
`fork()` ile yeni süreçler oluşturmak, yaşam döngülerini yönetmek (başlatma, bekletme, sonlandırma) ve `waitpid()` ile durumlarını analiz etmek.

### 🔗 Süreçler Arası İletişim (IPC)
`pipe()` ile birbirinden bağımsız çalışan iki program arasında tek yönlü bir veri tüneli kurmak.

### ↪️ I/O Yönlendirme (I/O Redirection)
`dup2()` ile bir programın ekran yerine bir dosyaya veya pipe'a yazmasını sağlamak.

### 📡 Sinyal Yönetimi (Signals)
`alarm()` ve `sigaction()` ile çalışan bir sürece dışarıdan müdahale etmek; `WIFEXITED`, `WIFSIGNALED` makrolarıyla sürecin neden sonlandığını anlamak.

---

## 📂 Egzersizler

### 1️⃣ ft_popen — Pipe & I/O Redirection

#### 📝 Görev

```c
int ft_popen(const char *file, char *const argv[], char type);
```

Bir programı `execvp` ile başlatır ve:
- `type == 'r'` → komutun **çıktısını** okumak için bir fd döner
- `type == 'w'` → komutun **girdisine** yazmak için bir fd döner
- Hata durumunda `-1` döner

#### 🔍 Çalışma Mantığı

```
ft_popen("ls", argv, 'r') çağrıldığında:

Ana Süreç                    Çocuk Süreç (fork sonrası)
─────────────────            ──────────────────────────
pipe() → [fd[0], fd[1]]      dup2(fd[1], STDOUT) ← ls'nin çıktısı buraya
fd[1]'i kapat                fd[0] ve fd[1]'i kapat
fd[0]'ı döner ←──── okur    execvp("ls", argv)
```

#### ⚠️ Kritik Nokta

> Kullanılmayan pipe uçlarını `close()` ile kapatmazsan, okuma tarafı asla EOF görmez ve programın **sonsuza kadar bekler (hanging)**.

#### 🧪 Test

```bash
cd ft_popen && make
./ft_popen
```

Beklenen çıktı:
```
--- Test 1: Okuma Modu ('r') [ls -la] ---
total XX
drwxr-xr-x ...
...

--- Test 2: Yazma Modu ('w') [wc -w] ---
4
```

---

### 2️⃣ picoshell — Multi-Process Pipeline

#### 📝 Görev

```c
int picoshell(char **cmds[]);
```

Shell'in boru hattı (`|`) mantığını uygular. `ls -la | grep main | wc -l` gibi birbirine bağlı komutları zincirir.

#### 🔍 Çalışma Mantığı

```
cmds = { ["ls","-la"], ["grep","main"], ["wc","-l"], NULL }

ls -la  ──pipe1──►  grep main  ──pipe2──►  wc -l  ──► STDOUT
  ↑ fork            ↑ fork                 ↑ fork
  in=-1             in=pipe1[0]            in=pipe2[0]
```

Her iterasyonda:
1. Yeni bir `pipe()` aç (son komut değilse)
2. `fork()` ile çocuk oluştur
3. Çocukta: önceki pipe'ın okuma ucunu `STDIN`'e, yeni pipe'ın yazma ucunu `STDOUT`'a bağla
4. Ana süreçte: kullanılmış fd'leri kapat, `in`'i güncelle

#### ⚠️ Kritik Nokta

> Her çocuk süreç, bir önceki komutun okuma ucunu devralmalıdır. **Sınır: 30 açık dosya.** Pipe fd'leri zamanında kapatılmazsa yüzlerce komutluk pipeline çalışmaz.

#### 🧪 Test

```bash
cd picoshell && make
./picoshell
```

Beklenen çıktı:
```
--- Picoshell Pipeline Testi Baslatiliyor ---
Calistirilacak Komut: ls -la | grep main | wc -l

Cikti:
2

Picoshell geri donus degeri: 0 (Beklenen: 0)
```

---

### 3️⃣ sandbox — Process Monitoring & Signals

#### 📝 Görev

```c
int sandbox(void (*f)(void), unsigned int timeout, bool verbose);
```

Bir fonksiyonun "iyi" mi "kötü" mü olduğunu denetler:
- `1` → fonksiyon başarıyla tamamlandı (exit code 0)
- `0` → fonksiyon kötü (segfault, timeout, hatalı exit kodu)
- `-1` → `sandbox`'ın kendi hatası

#### 🔍 Çalışma Mantığı

```
sandbox(f, timeout, verbose)
    │
    ├─► fork()
    │       │
    │       └─► Çocuk: f() çalışır → exit(0)
    │
    └─► Ana Süreç:
            │
            ├─ sigaction(SIGALRM) → handler kur
            ├─ alarm(timeout)     → zamanlayıcı başlat
            │
            ├─ waitpid() döndüyse:
            │       ├─ WIFEXITED   → exit kodu kontrol
            │       └─ WIFSIGNALED → sinyal adını yazdır (strsignal)
            │
            └─ waitpid() -1 döndüyse (EINTR):
                    └─ SIGALRM geldi → kill(pid, SIGKILL) → timeout mesajı
```

#### 📢 Verbose Mesajları

```
Nice function!
Bad function: exited with code <N>
Bad function: Segmentation fault
Bad function: timed out after <N> seconds
```

#### ⚠️ Kritik Nokta

> `alarm()` sinyali `waitpid()`'yi `EINTR` ile keser. `errno == EINTR` kontrolü yapılmazsa timeout sonrası hatalı davranış oluşur. Ayrıca **zombie process bırakılmamalı** — her `fork()` bir `waitpid()` ile karşılanmalı.

#### 🧪 Test

```bash
cd sandbox && make
./sandbox
```

Beklenen çıktı:
```
=== 1. TEST: Nice Function ===
Nice function!
Result: 1 (Beklenen: 1)

=== 2. TEST: Bad Function (Segfault) ===
Bad function: Segmentation fault
Result: 0 (Beklenen: 0)

=== 3. TEST: Bad Function (Timeout) ===
Bad function: timed out after 2 seconds
Result: 0 (Beklenen: 0)
```

---

## 🚀 Kurulum

### Gereksinimler

- C derleyici: `cc` / `gcc`
- Unix benzeri sistem: Linux, macOS, WSL
- GNU Make

### Derleme

```bash
# Repoyu klonla
git clone https://github.com/skarayil/unix-system-programming-rank04.git
cd unix-system-programming-rank04

# Her egzersizi ayrı ayrı derle
cd ft_popen && make && cd ..
cd picoshell && make && cd ..
cd sandbox   && make && cd ..
```

### Temizlik

```bash
make fclean   # binary + object dosyaları sil
make re       # temizle ve yeniden derle
```

---

## 📚 Temel Kavramlar

### `fork()` ve Süreç Ağacı

```c
pid_t pid = fork();

if (pid == -1) { /* hata */ }
if (pid == 0)  { /* çocuk süreç */ }
else           { /* ana süreç, pid = çocuğun PID'i */ }
```

### `pipe()` ve Veri Akışı

```c
int fd[2];
pipe(fd);
// fd[0] → okuma ucu (read end)
// fd[1] → yazma ucu (write end)
```

### `dup2()` ile Yönlendirme

```c
dup2(fd[1], STDOUT_FILENO);
// Artık printf() → fd[1] → pipe'a yazar
```

### `waitpid()` Status Makroları

| Makro | Anlamı |
|-------|--------|
| `WIFEXITED(status)` | Süreç `exit()` ile mi bitti? |
| `WEXITSTATUS(status)` | `exit()` kodu neydi? |
| `WIFSIGNALED(status)` | Süreç sinyal ile mi öldürüldü? |
| `WTERMSIG(status)` | Hangi sinyal? |

### Sinyal Akışı (`sandbox` için)

```
alarm(N) ──N saniye geçince──► SIGALRM ──► handler ──► waitpid EINTR döner
                                                              │
                                                    kill(pid, SIGKILL)
                                                    waitpid(pid, NULL, 0)
```

---

## ⚠️ Yaygın Hatalar

| Hata | Sonuç | Çözüm |
|------|-------|-------|
| Pipe fd'lerini kapatmamak | Hanging (sonsuz bekleme) | Her kullanılmayan ucu `close()` ile kapat |
| `fork()` sonrası `wait()` yazmamak | Zombie process | Her çocuk için `waitpid()` kullan |
| `errno` kontrolü yapmamak | Timeout'u atlamak | `waitpid` `-1` dönünce `errno == EINTR` kontrol et |
| `execvp` sonrası `exit()` yazmamak | Çocuk ana kodunu çalıştırır | `execvp` başarısız olursa mutlaka `exit(1)` |
| `in` fd'yi zamanında kapatmamak | Dosya limiti aşımı | Her iterasyonda önceki `in`'i kapat |

---

<div align="center">

*Bu üç egzersizi bitirdiğinde, işletim sisteminin süreçleri nasıl yönettiğini,*
*veriyi bir yerden bir yere nasıl taşıdığını ve hataları nasıl raporladığını*
*somut olarak kavramış olacaksın.*

### 👩‍💻 Created by Sude Naz Karayıldırım

**⭐ Eğer bu proje işinize yaradıysa, repo'ya star vermeyi unutmayın!**

[![42 Profile](https://img.shields.io/badge/42%20Profile-skarayil-black?style=flat-square&logo=42&logoColor=white)](https://profile.intra.42.fr/users/skarayil)
[![GitHub](https://img.shields.io/badge/GitHub-skarayil-181717?style=flat-square&logo=github&logoColor=white)](https://github.com/skarayil)


</div>
