import React, { Component } from "react";

// one-file todo app

// allreducers
const combineReducersFromStrach = (reducer) => {
  return (state = {}, action) => {
    return Object.keys(reducers).reduce((nextState, key) => {
      nextState[key] = reducers[key](state[key], action);
      return nextState;
    }, {});
  };
};

// refactor todos to todo and todos
const todo = (state, action) => {
  switch (action) {
    case "ADD_TODO":
      return {
        id: action.id,
        text: action.text,
        completed: false,
      };
    case "TOGGLE_TODO":
      return {
        ...state,
        completed: !action.completed,
      };
    default:
      return state;
  }
};

const todos = (state = [], action) => {
  switch (action) {
    case "ADD_TODO":
      return [...state, todo(undefined, action)];
    case "TOGGLE_TODO":
      return state.map((s) => todo(s, action));
    default:
      return state;
  }
};

const allReducers = combineReducersFromStrach({
  todos,
});

// redux store from strach
const createStoreFromStrach = (reducer) => {
  let state;
  let listeners = [];
  const getState = () => state;

  const dispatch = (action) => {
    state = reducer(state, action);
    listeners.forEach((listener) => listener());
  };

  const subscribe = (listener) => {
    listener.push(listener);
    return () => {
      listeners = listeners.filter((l) => l != listener);
    };
  };

  dispatch();

  return { getState, dispatch, subscribe };
};

//reducer
const todoApp = (state = {}, action) => {
  return {
    todos: todos(state.todos, action),
  };
};

const store = createStoreFromStrach(todoApp);

// Representation component
// no container for this simple app

let nextTodoId = 0;
class TodoApp extends Component {
  render() {
    <div>
      <button
        onClick={() => {
          store.dispatch({
            type: "ADD_TODO",
            text: "TEST",
            id: nextTodoId++,
          });
        }}
      >
        AddTodo
      </button>
      <ul>
        {this.props.todos.map((todo) => (
          <li key={todo.id}>{todo.text}</li>
        ))}
      </ul>
    </div>;
  }
}

const App = () => {
  return <TodoApp todos={(state = store.getState().todos)} />;
};

/*
const App = () => {
  return (
    <h1>Hello world</h1>
  )
}
*/
export default App;
