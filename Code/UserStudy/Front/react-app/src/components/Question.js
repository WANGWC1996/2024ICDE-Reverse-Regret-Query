import React from "react";
import { connect } from "react-redux";
import {
  setActiveComponent,
  setInteractionResult,
  setLeftPoints,
  setScore,
  prunePoints,
  updateConvexHull, 
  setEstU
} from "../actions";
import {
  array2Vector2D,
  vector2Array,
  getPrunedIndices,
  vector2Array2D
} from "../utils";

const SIMPLEX = 2;
const RANDOM = 1;

// iteratively ask the user to choose the preferred car from a pair of cars.
class Question extends React.Component {
  constructor(props) {
    super(props);
    const smallerBetter = new window.Module.VectorInt();
    this.attributes = [];
    this.props.attributes.forEach(([attr, config]) => {
      if (this.props.mask[attr]) {
        smallerBetter.push_back(config.smallerBetter ? 1 : 0);
        this.attributes.push(attr);
      }
    });
    const candidatesVec = array2Vector2D(this.props.candidates);
    this.runner = new window.Module.AlgorithmRunner(
      candidatesVec,
      smallerBetter,
      this.props.mode === "random" ? RANDOM : SIMPLEX
    );
    candidatesVec.delete();
    const indices = this.runner.nextPair();
    this.state = {
        pair: vector2Array(indices),
        interRR: []
    };
  }

  choose = idx => {
    const option = idx + 1;
    //record the interaction result
    const trs = this.state.pair.map((idx, i) => {
      let tds = "\n";
      this.props.candidates[idx].forEach((x, j) => {
        tds += x.toString();
        tds += "  ";
      });
      return tds;
    });
    trs.push("\n");
    trs.push(option);
    trs.push("\n");
    console.log(trs);
    this.state.interRR.push(trs);

    const accurracy = this.runner.choose(option);
    if (accurracy > 0.99999)
    {
      this.stopInteraction();
    }
    else {
      const indices = this.runner.nextPair();
      this.setState({
        pair: vector2Array(indices)
      });
    }
  };

  stopInteraction = () => {
    //this.prevIndices.delete();
    const Indicess = this.runner.getRanking();
    this.props.setLeftPoints(vector2Array(Indicess));
    const Scores = this.runner.getScore();
    this.props.setScore(vector2Array(Scores));
    const Uvector = this.runner.getU();
    this.props.setEstU(vector2Array(Uvector));
    this.runner.delete();
    this.props.showResult(this.state.interRR);
};

render() {
const ths = [<th key="Option No.">Option</th>];
this.attributes.forEach(attr => {
  ths.push(<th key={attr}>{attr}</th>);
});
ths.push(<th key="chooseButton" />);

const trs = this.state.pair.map((idx, i) => {
  const tds = [<td key="Option No.">{i + 1}</td>];
  this.props.candidates[idx].forEach((x, j) => {
    tds.push(<td key={j}>{x}</td>);
  });
  tds.push(
    <td key="chooseButton">
      <button
        type="button"
        className="btn btn-outline-success btn-sm"
        onClick={() => this.choose(i)}
      >
        Choose
      </button>
    </td>
  );
  return (
    <tr key={i} data-toggle="tooltip" title={this.props.labels[idx]}>
      {tds}
    </tr>
  );
});

return (
  <div>
    <h3>Phase One: Interaction  </h3>
    <br/><br/>
    <h4>
      Q{this.runner.getNumQuestion()}: Choose the Car you favor more
      between the following options
    </h4>
    <div className="row justify-content-center align-items-center">
      <div className="col-md-8">
        <table className="table table-hover text-center">
          <thead>
            <tr>{ths}</tr>
          </thead>
          <tbody>{trs}</tbody>
        </table>
      </div>
    </div>
  </div>
);
}
}

const mapStateToProps = ({ labels, candidates, mask, attributes, numLeftPoints, mode, scores, approU }) => ({
    labels,
    candidates,
    mask,
    attributes,
    numLeftPoints,
    mode,
    scores, 
    approU
});

const mapDispatchToProps = dispatch => ({
  showResult: (interResults) => {
    dispatch(setInteractionResult(interResults));
    dispatch(setActiveComponent("PhaseTwo"));
  },
  setLeftPoints: indices => { dispatch(setLeftPoints(indices));},
  setScore: scores => { dispatch(setScore(scores));},
  setEstU: Uvector => { dispatch(setEstU(Uvector))},
  prunePoints: (indices, step) => { dispatch(prunePoints(indices, step));},
  updateConvexHull: vertices => {dispatch(updateConvexHull(vertices)); }
});

export default connect(
mapStateToProps,
mapDispatchToProps
)(Question);
