# Modüler Analitik Collatz Simülasyonu ve Otonom Denetim Mimarisi

## 1. Giriş ve Mimari Genel Bakış
Collatz sanısı ($3x + 1$ problemi), klasik bilgisayar bilimlerinde genellikle devasa kaynaklar tüketen kaba kuvvet (brute-force) algoritmalarıyla taranır. Ancak bu çalışmada geliştirilen sistem; C++ tabanlı yüksek hızlı bir hesaplama motoru ile Python tabanlı otonom bir denetçi katmanını birleştirerek, donanımı yormadan (fan-silent çalışma prensibiyle) milyarlarca adımı hatasız bir şekilde işlemektedir.

Sistem, adımları tek tek hesaplamak yerine modüler aritmetik ve bit-ölçekli analizler kullanarak analitik sıçramalar gerçekleştirir. Python orkestratörü (`run_orchestrator.py`), her $100$ saniyede bir arka planda çalışan eşzamanlı bir iş parçacığı (**autonomous auditor thread**) aracılığıyla log dosyalarını denetler, matematiksel tutarlılığı ($Audits = 0$) doğrular ve sistem housekeeping döngüsünü yönetir.

## 2. Proje Kaynak Kodları
Geliştirdiğimiz bu otonom motorun kaynak kodlarına, C++ optimizasyonlarına ve Python otomasyon betiklerine bu repository üzerinden ulaşabilirsin.

## 3. Python Döngüsü ve Rasyonel Sayıların Potansiyel Sonsuzluğu
Sistemin mimari tasarımı, matematiksel sonsuzluk kavramı ile yazılım döngüleri arasında derin bir analoji kurar. Rasyonel sayılar kümesi $\mathbb{Q}$ sonsuzdur ancak **sayılabilirdir** ($\mathbb{N}$ ile birebir eşlenebilir). 

Yazdığımız Python otomasyon döngüsü de bu mantığı takip eder:
* **Potansiyel Sonsuzluk (Potential Infinity):** Donanım ve zaman sınırları elverdiği sürece, döngü her periyotta yeni bir sayı aralığını işlemeye devam eder. Asla "tamamlandı" nihai noktasına ulaşmaz; tıpkı rasyonel sayıların yoğunluk özelliğinde her iki sayı arasında sonsuz sayıda başka eleman bulunabilmesi gibi sürekli genişleyen bir süreç sunar.
* **Deneysel Laboratuvar:** Python betiğinin arkada logları temizleyerek sonsuz bir döngüde çalışması, sonlu bir donanım üzerinde potansiyel sonsuzluğun simüle edilmesini sağlayan en zarif deneysel yaklaşımlardan biridir.
