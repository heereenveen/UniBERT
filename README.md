# **UniBERT**

UniBERT is a chatbot to help students of the Faculty of Physical Engineering and Technology (KPI), which uses the large BERT language model to solve problems in the field of **question-answer** (QA). The chatbot generates textual answers to students' questions regarding student life, faculties, schedules, teachers, and other aspects of the educational process.

## **Project features**
- The system is based on a **LLM based on the BERT transformer** trained on open data posted on university websites.
- Generating accurate answers to natural user questions.
- Frontend: A cross-platform **C++** application developed using **Qt**.

## **Examples of Use**

- **Q:** Який розклад у понеділок на перший тиждень у групи ІМ-21?  
  **A:**  
  1. Операційні системи.  
  2. Компоненти комп'ютерних систем.  
  3. Англійська.

- **Q:** Хто викладає дисципліну Операційні системи?  
  **A:** Андрій Симоненко.

- **Q:** Коли починається перша атестація у першому семестрі?  
  **A:** 14 жовтня.

## **Виконані завдання**

### **№ 2  Налаштування проекту та інструментів розробки**

@heereenveen:
    Створені пакети та модуль для моделі, налаштовані лінтери та форматтери для Python, не забуваючи про git-хуки:
    https://github.com/heereenveen/UniBERT/commit/29481d10119d878f6a279499361b56cc87158ab0

@notnuff:
- Створений проєкт для клієнту (CMakeLists.txt);
- Обраний стиль коду для проєкту (Google code style);
- Налаштований лінтер та форматтер (clang-format);
- Налаштовані хуки на комміт і пуш, з необхідними перевірками 
(PS: щоб їх побачити, необхідно вивантажити директорію і заглянути в .git/pre-push та .git/pre-commit)
- Також підключені Github Actions;
- link: https://github.com/heereenveen/UniBERT/pull/6
    

### **№ 3  Розробка структури застосунку**

@heereenveen:
  Модель була розділена на декілька пакетів для поступової роботи усього пайплайну моделі: 
  отримати дані -> препарувати їх -> запустити навчену модель -> отримати питання -> надіслати вірогідну відповідь.
  Це було відображено також у графіках роботи системи.
  https://github.com/heereenveen/UniBERT/commit/bace959a1d27891739324db65cba1045c85c3230

@notnuff:
    Клієнт було вирішено зробити за традиційною схемою Model/View/Controller.
    Згідно такого плану:
- у Model буде відповідальність за комунікацію з сервером і, 
    ймовірно, за збереження історії повідомлень. 
- View відповідатиме за відображення історії запитів користувачу, 
    а також за надання користувачу інтерфейсу спілкування з текстовою моделлю
- Controller в свою чергу відповідатиме за обробку запитів користувача,
    передання їх в Model, і відповідно відображення відповідей від сервера у чат View
- link: https://github.com/heereenveen/UniBERT/pull/8

### **№ 4  Імплементація інтерактивного прототипу**

@heereenveen:
  Імплементовано:
  https://github.com/heereenveen/UniBERT/commit/64b26e84a29771a76c6085a3c1d1f146fcfc887a

@notnuff:
  Імплементовано:
  https://github.com/heereenveen/UniBERT/pull/9
  
### **№ 5  Імплементація інтеграції з віддаленими джерелами даних**

@heereenveen:
    Саму модель було натреновано на корпусі контекстів з відповіддями, після чого було [розміщено](https://huggingface.co/heereenveen/bert_qa_fiot) на платформі HuggingFace.
    Під час ініціалізації програми вона вивантажує модель з платформи та використовує її для QA-процесу.
    https://github.com/heereenveen/UniBERT/commit/e168e330b4840ede956050e1b8d7840a693d225d#diff-8c26351b04b3158996fbb6d2ebe941418658927b1f6755a4f3cc170aa48c0910

@notnuff:

### **№ 7  Розгортання програмного забезпечення**

@heereenveen:

@notnuff:
