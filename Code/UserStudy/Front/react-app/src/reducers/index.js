import { combineReducers } from "redux";
import {
  SET_ACTIVE_COMPONENT,
  SET_DATASET,
  SET_CANDIDATES,
  TOGGLE_MASK,
  SET_LEFT_POINTS,
  PRUNE_POINTS,
  SET_MODE,
  RESTART,
  UPDATE_CONVEX_HULL,
  SET_SCORE,
  SET_NAME,
  SET_EMAIL,
  SET_INTERACTION_RESULT, 
  SET_EST_U
} from "../actions";


const approU = (state = null, action) => {
  switch (action.type) {
    case SET_EST_U:
      return action.approU;
    default:
      return state;
  }

}


const activeComponent = (state = "Welcome", action) => {
  switch (action.type) {
    case SET_ACTIVE_COMPONENT:
      return action.component;
    default:
      return state;
  }
};

// all points in the dataset
const points = (state = null, action) => {
  switch (action.type) {
    case SET_DATASET:
      return action.points;
    default:
      return state;
  }
};

//the scores of all points in the dataset
const scores = (state = null, action) => {
  switch (action.type) {
    case SET_SCORE:
      return action.scores;
    default:
      return state;
  }
}


// the labels of points
const labels = (state = null, action) => {
  switch (action.type) {
    case SET_DATASET:
      return action.labels;
    default:
      return state;
  }
};

// the attribute names
const attributes = (state = null, action) => {
  switch (action.type) {
    case SET_DATASET:
      return action.attributes;
    default:
      return state;
  }
};

// the set of points in the specified ranges.
const candidates = (state = null, action) => {
  switch (action.type) {
    case SET_CANDIDATES:
      return action.candidates;
    default:
      return state;
  }
};

// show/hide attributes (this feature is not exposed in the UI)
const mask = (state = null, action) => {
  switch (action.type) {
    case SET_DATASET:
      const mask = {};
      action.attributes.forEach(([attr, config]) => {
        mask[attr] = 1;
      });
      return mask;
    case TOGGLE_MASK:
      return { ...state, ...action.mask };
    default:
      return state;
  }
};

// the set of points pruned.
// it is an array of [idx, step no.]
const prunedPoints = (state = [], action) => {
  switch (action.type) {
    case RESTART:
      return [];
    case PRUNE_POINTS:
      const points = action.indices.map(idx => [idx, action.step]);
      return [...points, ...state];
    default:
      return state;
  }
};

// the set of candidate points
// it is an array of indices
const leftPoints = (state = [], action) => {
  switch (action.type) {
    case RESTART:
      return [];
    case SET_LEFT_POINTS:
      return action.indices;
    case PRUNE_POINTS:
      return state.filter(idx => action.indices.indexOf(idx) === -1);
    default:
      return state;
  }
};

// history of the number of left points
const numLeftPoints = (state = [], action) => {
  switch (action.type) {
    case SET_LEFT_POINTS:
      return [action.indices.length];
    case PRUNE_POINTS:
      const prev = state[state.length - 1];
      return [...state, prev - action.indices.length];
    default:
      return state;
  }
};

// the algorithm to select a pair of points.
const mode = (state = "simplex", action) => {
  switch (action.type) {
    case SET_MODE:
      return action.mode;
    default:
      return state;
  }
};

// vertices of the convex hull of the preference space.
const vertices = (state = [], action) => {
  switch (action.type) {
    case UPDATE_CONVEX_HULL:
      return action.vertices;
    default:
      return state;
  }
};

const userName = (state = null, action) => {
  switch (action.type) {
    case SET_NAME:
      return action.name;
    default:
      return state;
  }
};

const userEmail = (state = null, action) => {
  switch (action.type) {
    case SET_EMAIL:
      return action.email;
    default:
      return state;
  }
};

const interactionResults = (state = null, action) => {
  switch (action.type) {
    case SET_INTERACTION_RESULT:
      return action.interactionResults;
    default:
      return state;
  }
};


export default combineReducers({
  activeComponent,
  points,
  labels,
  attributes,
  candidates,
  mask,
  prunedPoints,
  leftPoints,
  numLeftPoints,
  mode,
  vertices,
  scores,
  userName,
  userEmail,
  interactionResults, 
  approU
});
