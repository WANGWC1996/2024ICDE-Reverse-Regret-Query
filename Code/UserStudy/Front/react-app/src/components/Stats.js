import React from "react";
import { connect } from "react-redux";
import classNames from "classnames";

// statistics including the number of cars pruned/left.
class Stats extends React.Component {
  constructor(props) {
    super(props);
    this.attributes = [];
    this.props.attributes.forEach(([attr, config]) => {
      if (this.props.mask[attr]) {
        this.attributes.push(attr);
      }
    });
  }

  render() {
    let ths = [<th key="Step No.">Step</th>];
    this.attributes.forEach(attr => {
      ths.push(<th key={attr}>{attr}</th>);
    });
    const prunedTrs = this.props.prunedPoints.map(([idx, step], i) => (
      <tr key={i} data-toggle="tooltip" title={this.props.labels[idx]}>
        {[step, ...this.props.candidates[idx]].map((x, j) => (
          <td key={j}>{x}</td>
        ))}
      </tr>
    ));
    const leftTrs = this.props.leftPoints.map((idx, i) => (
      <tr key={i} data-toggle="tooltip" title={this.props.labels[idx]}>
        {this.props.candidates[idx].map((x, j) => (
          <td key={j}>{x}</td>
        ))}
      </tr>
    ));
    return (
      <div>
        <h2>Statistics</h2>
        <div className="row">
          <div className="col">
            <h4>The No. of Cars Pruned: {this.props.prunedPoints.length}</h4>
            <table
              className={classNames("table", "table-hover", {
                "table-fixed": prunedTrs.length > 7
              })}
              style={{
                minWidth: "37rem"
              }}
            >
              <thead>
                <tr>{ths}</tr>
              </thead>
              <tbody>{prunedTrs}</tbody>
            </table>
          </div>
          <div className="col">
            <h4>
              The No. of Cars Left in the Database:{" "}
              {this.props.leftPoints.length}
            </h4>
            <table
              className={classNames("table", "table-hover", {
                "table-fixed": leftTrs.length > 7
              })}
              style={{
                minWidth: "30rem"
              }}
            >
              <thead>
                <tr>{ths.slice(1)}</tr>
              </thead>
              <tbody>{leftTrs}</tbody>
            </table>
          </div>
        </div>
      </div>
    );
  }
}

const mapStateToPropsStats = ({
  labels,
  candidates,
  prunedPoints,
  leftPoints,
  attributes,
  mask
}) => ({
  labels,
  candidates,
  prunedPoints,
  leftPoints,
  attributes,
  mask
});

export default connect(mapStateToPropsStats)(Stats);
