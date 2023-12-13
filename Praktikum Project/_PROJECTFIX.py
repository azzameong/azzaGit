import tkinter as tk
from tkinter import messagebox
from tkinter import ttk

import time
import threading
import pygame

def play():
    pygame.mixer.init()
    pygame.mixer.music.load("alert.wav")
    pygame.mixer.music.play(loops=0)

class PomodoroTimer:
    def __init__(self, root):
        self.root = root
        self.root.title("SAE Study Timer")
        self.root.configure(bg="#E3C4A8")  # BG color

        # Header
        self.header_frame = tk.Frame(root, bg="#4592AF")  # Header color
        self.logo_image = tk.PhotoImage(file="LOGO_PEMLAN.png")
        self.logo_image_resized = self.logo_image.subsample(5, 5)
        self.logo_label = tk.Label(self.header_frame, image=self.logo_image_resized, bg="#4592AF")
        self.logo_label.pack(side=tk.LEFT, padx=10)
        self.title_label = tk.Label(self.header_frame, text="SAE Study Timer", font=("Montserrat", 32, "bold"), bg="#4592AF", fg="white")
        self.title_label.pack(side=tk.RIGHT, padx=300, pady=10, anchor="center")

        # Center Title
        center_label = tk.Label(self.header_frame, bg="#4592AF")
        center_label.pack(side=tk.LEFT, fill=tk.X, expand=True)

        self.header_frame.pack(fill=tk.X, padx=10, pady=10)

        # Separate Line
        self.canvas = tk.Canvas(root, height=30, bg="#33313B", highlightthickness=0)  # Set separating line color
        self.canvas.pack(fill=tk.X, padx=10)

        # Separate Window
        self.paned_window = tk.PanedWindow(root, orient=tk.HORIZONTAL, sashrelief=tk.RAISED, sashwidth=5)
        self.paned_window.pack(expand=True, fill=tk.BOTH, padx=10, pady=10)

        # Set button style
        style = ttk.Style()
        style.configure('Rounded.TButton', foreground='#33313B', background='white')

        # Left pane for To-Do List
        self.left_frame = tk.Frame(self.paned_window, bg="#E3C4A8")
        self.todo_entry = tk.Entry(self.left_frame, font=("Montserrat", 16)) 
        self.todo_entry.pack(pady=30, ipady=10)

        button_frame = tk.Frame(self.left_frame, bg="#E3C4A8")
        button_frame.pack()

        self.add_todo_button = ttk.Button(button_frame, text="Add To-Do", command=self.add_todo, style='Rounded.TButton')
        self.add_todo_button.pack(side=tk.LEFT, padx=(0, 5), pady=5, ipady=2)
        self.remove_todo_button = ttk.Button(button_frame, text="Remove To-Do", command=self.remove_todo, style='Rounded.TButton')
        self.remove_todo_button.pack(side=tk.LEFT, pady=5, ipady=2)

        # Center the To-Do List
        self.todo_listbox = tk.Listbox(self.left_frame, selectmode=tk.SINGLE, font=("Montserrat", 14), height=8)
        self.todo_listbox.pack(pady=5, ipady=10, anchor=tk.CENTER)

        # Right pane for Timer
        self.right_frame = tk.Frame(self.paned_window, bg="#E3C4A8")

        # Center the Timer
        self.label = tk.Label(self.right_frame, text="", font=("Montserrat", 72), bg="#E3C4A8")
        self.label.pack(pady=10, expand=True, anchor=tk.CENTER)

        button_frame = tk.Frame(self.right_frame, bg="#E3C4A8")
        button_frame.pack(pady=5)

        self.start_button = ttk.Button(button_frame, text="Start", command=self.start_timer, style='Rounded.TButton')
        self.start_button.grid(row=0, column=0, padx=10, pady=(0, 5), ipady=2, sticky="ew")

        self.stop_button = ttk.Button(button_frame, text="Pause", command=self.stop_timer, style='Rounded.TButton')
        self.stop_button.grid(row=0, column=1, padx=10, pady=(0, 5), ipady=2, sticky="ew")

        self.reset_button = ttk.Button(button_frame, text="Reset", command=self.reset_timer, style='Rounded.TButton')
        self.reset_button.grid(row=1, column=0, columnspan=2, pady=(0, 5), padx=10, sticky="ew")

        # Frame Window
        self.paned_window.add(self.left_frame)
        self.paned_window.add(self.right_frame)

        # Same Size Frame Window
        self.paned_window.add(self.left_frame, stretch="always")
        self.paned_window.add(self.right_frame, stretch="always")

        # Initialize timer
        self.work_time = 25 * 60 #25 menit
        self.break_time = 5 * 60 #5 menit 
        self.current_time = self.work_time
        self.in_break_time = False
        self.timer_running = False

    def add_todo(self):
        todo_text = self.todo_entry.get().strip()
        if todo_text:
            self.todo_listbox.insert(tk.END, todo_text)
            self.todo_entry.delete(0, tk.END)

    def remove_todo(self):
        selected_index = self.todo_listbox.curselection()
        if selected_index:
            self.todo_listbox.delete(selected_index)
    
    def start_timer(self):
        if not self.timer_running:
            self.timer_running = True
            self.start_button.config(state=tk.DISABLED)
            self.stop_button.config(state=tk.NORMAL)
            self.reset_button.config(state=tk.DISABLED)
            self.todo_entry.config(state=tk.DISABLED)
            self.add_todo_button.config(state=tk.DISABLED)
            self.remove_todo_button.config(state=tk.DISABLED)
            self.timer_thread = threading.Thread(target=self.run_timer)
            self.timer_thread.start()

    def stop_timer(self):
        if self.timer_running:
            self.timer_running = False
            self.start_button.config(state=tk.NORMAL)
            self.stop_button.config(state=tk.DISABLED)
            self.reset_button.config(state=tk.NORMAL)
            self.todo_entry.config(state=tk.NORMAL)
            self.add_todo_button.config(state=tk.NORMAL)
            self.remove_todo_button.config(state=tk.NORMAL)

            if self.timer_thread:
                self.timer_thread.join()

    def reset_timer(self):
        self.stop_timer()
        self.current_time = self.work_time
        self.in_break_time = False
        self.update_label()

    def run_timer(self):
        while self.timer_running and self.current_time > 0:
            self.update_label()
            time.sleep(1)
            self.current_time -= 1

        if self.timer_running:
            self.timer_running = False
            self.start_button.config(state=tk.NORMAL)
            self.stop_button.config(state=tk.DISABLED)
            self.reset_button.config(state=tk.NORMAL)
            self.todo_entry.config(state=tk.NORMAL)
            self.add_todo_button.config(state=tk.NORMAL)
            self.remove_todo_button.config(state=tk.NORMAL)

            if self.current_time == 0:
                play()
                if self.in_break_time:
                    self.show_message("Waktu Habis!")
                    self.current_time = self.work_time
                    self.in_break_time = False
                else:
                    self.show_message("Saatnya Istirahat!")
                    self.current_time = self.break_time
                    self.in_break_time = True

            self.update_label()
            self.start_timer()

    def update_label(self):
        minutes, seconds = divmod(self.current_time, 60)
        time_str = f"{minutes:02d}:{seconds:02d}"
        self.label.config(text=time_str)

    def show_message(self, message):
        messagebox.showinfo(" Study Timer", message)



if __name__== "__main__":
    root = tk.Tk()
    app = PomodoroTimer(root)
    root.mainloop()