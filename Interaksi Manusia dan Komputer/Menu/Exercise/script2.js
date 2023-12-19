document.addEventListener("DOMContentLoaded", function () {
    const taskInput = document.querySelector(".taskAdder input");
    const taskBox = document.querySelector(".task-box");
  
    let todos = JSON.parse(localStorage.getItem("todo-list")) || [];
  
    function showTodo() {
      let li = "";
      todos.forEach((todo, id) => {
        console.log(id, todo);
        li += `<li class="task">
                  <label for="${id}">
                      <input type="checkbox" id="${id}" data-index="${id}">
                      <p>${todo.name}</p>
                  </label>
              </li>`;
      });
      taskBox.innerHTML = li;
  
      // Add event listeners for checkboxes
      const checkboxes = document.querySelectorAll('.task-box input[type="checkbox"]');
      checkboxes.forEach(checkbox => {
        checkbox.addEventListener("change", handleCheckboxChange);
      });
    }
  
    function handleCheckboxChange(event) {
      const index = event.target.dataset.index;
      // Remove the task from the array
      todos.splice(index, 1);
      // Update local storage
      localStorage.setItem("todo-list", JSON.stringify(todos));
      // Update the displayed list
      showTodo();
    }
  
    showTodo();
  
    taskInput.addEventListener("keyup", (e) => {
      let userTask = taskInput.value.trim();
      if (e.key === "Enter" && userTask) {
        taskInput.value = "";
        let taskInfo = { name: userTask };
        todos.push(taskInfo);
        localStorage.setItem("todo-list", JSON.stringify(todos));
        showTodo();
      }
    });
  });
  