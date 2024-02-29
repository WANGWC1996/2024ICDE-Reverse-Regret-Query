export const SET_ACTIVE_COMPONENT = "SET_ACTIVE_COMPONENT";
export const SET_CANDIDATES = "SET_CANDIDATES";
export const SET_DATASET = "SET_DATASET";
export const TOGGLE_MASK = "TOGGLE_MASK";
export const PRUNE_POINTS = "PRUNE_POINTS";
export const SET_LEFT_POINTS = "SET_LEFT_POINTS";
export const SET_MODE = "SET_MODE";
export const RESTART = "RESTART";
export const UPDATE_CONVEX_HULL = "UPDATE_CONVEX_HULL";
export const SET_SCORE = "SET_SCORE";
export const SET_NAME = "SET_NAME";
export const SET_EMAIL = "SET_EMAIL";
export const SET_INTERACTION_RESULT = "SET_INTERACTION_RESULT";
export const SET_EST_U = "SET_EST_U";

export const setEstU = approU => ({
  type: SET_EST_U,
  approU
});

export const setInteractionResult = interactionResults => ({
  type: SET_INTERACTION_RESULT,
  interactionResults
});

export const setUserName = name => ({
  type: SET_NAME,
  name
});

export const setUserEmail = email => ({
  type: SET_EMAIL,
  email
});

export const setActiveComponent = component => ({
  type: SET_ACTIVE_COMPONENT,
  component
});

export const setCandidates = candidates => ({
  type: SET_CANDIDATES,
  candidates
});

export const setDataset = (points, labels, attributes) => ({
  type: SET_DATASET,
  points,
  labels,
  attributes
});

export const toggleMask = (attr, val) => ({
  type: TOGGLE_MASK,
  mask: { [attr]: val }
});

export const prunePoints = (indices, step) => ({
  type: PRUNE_POINTS,
  indices,
  step
});

export const setLeftPoints = indices => ({
  type: SET_LEFT_POINTS,
  indices
});

export const setScore = scores => ({
  type: SET_SCORE,
  scores
})

export const changeMode = mode => ({
  type: SET_MODE,
  mode
});

export const restart = () => ({
  type: RESTART
});

export const updateConvexHull = vertices => ({
  type: UPDATE_CONVEX_HULL,
  vertices
});
