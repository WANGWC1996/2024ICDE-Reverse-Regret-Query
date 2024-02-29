import React from "react";
import { connect } from "react-redux";
import classNames from "classnames";
import { setActiveComponent, restart } from "../actions";
import Histogram from "./Histogram";

class Result extends React.Component {
  constructor(props) {
    super(props);
    this.ths = [];
    this.props.attributes.forEach(([attr, config]) => {
      if (this.props.mask[attr]) {
        const th = <th key={attr}>{attr}</th>;
        this.ths.push(th);
      }
    });
    this.ths.push(<th key="chooseCheckbox"/>);

    //ranked points withpoints and ranking
    this.pointsScoreRanking = [];
    for(let i = 0; i < this.props.leftPoints.length; ++i)
    {
      let pt = [], index = this.props.leftPoints[i];
      for(let j = 0; j < this.props.candidates[index].length; ++j)
        pt.push(this.props.candidates[index][j]);
      pt.push(this.props.scores[i]);
      pt.push(i+1);
      this.pointsScoreRanking.push(pt);
    }

    //ranked points in html
    this.trs = this.props.leftPoints.map((idx, i) => (
        <tr key={i} data-toggle="tooltip" title={this.props.labels[idx]}>
          {this.props.candidates[idx].map((x, j) => (
              <td key={j}>{x}</td>
          ))}
          <td key="chooseCheckbox"/>
        </tr>
    ));

    //points for presenting
    const top = [this.trs[0]];
    const top1small = [], top1large = [];
    for (let i = 1; i < this.props.leftPoints.length; ++i)
    {
      if ((this.props.scores[0] - this.props.scores[i]) / this.props.scores[0] < 0.1)
        top1small.push(this.pointsScoreRanking[i]);
      else
        top1large.push(this.pointsScoreRanking[i]);
    }
    const top1smallSample = [], top1largeSample = [];
    if(top1small.length < 5)
    {
        for (let i = 0; i < top1small.length; ++i)
        {
            console.log(i);
            top1smallSample.push(top1small[i]);
        }
    }
    else
    {
        for (let i = 1; i < 6 && i <= top1small.length; ++i)
        {
            let indexx = Math.floor(i/5 * top1small.length - 1);
            console.log(indexx);
            if(indexx >= 0)
                top1smallSample.push(top1small[indexx]);
        }
    }
    for (let i = 1; i < 6 && i < top1large.length; ++i)
    {
        let indexx = Math.floor(i/5 * top1large.length - 1);
        if(indexx >= 0)
            top1largeSample.push(top1large[indexx]);
    }

    const present = [];
    present.push(this.props.approU);
    present.push("\n");
    for(let i = 0; i < this.props.leftPoints.length; ++i)
    {
      present.push(this.pointsScoreRanking[i].map((x, j) => { return (x); }));
      present.push("\n");
    }

    let checkboxValues = {};
    for (let i = 0; i < 10; i++) {
      checkboxValues[`myCheckbox${i}`] = false;
    }

    this.state = {
      intro: "According to our learning algorithm, we found that your favorite car is shown as follows.",
      inst1: "Although we know your favorite car, in this study, we also want to see whether you are interested in some cars outside your favorite car. Thus, we select the following cars which are not your favorite car. They may be interesting to you. Please COMPARE your favorite car shown above and the following cars, and indicate if you are interested in the following cars (in addition to your favorite car shown above). You could select 0, one, or more than one cars in which you are interested in the following list.",
      inst2: "We believe that you are NOT interested in the following cars. Please compare your favorite car shown above and the following cars, and indicate if you are NOT interested in the following cars? You could select 0, one, or more than one cars in which you are NOT interested in the following list.",
      ths: this.ths,
      top: top,
      topSamples: top1smallSample,
      topSamplel: top1largeSample,
      output: present,
      checkboxValues: checkboxValues
    };

  }
  
  pickRandom = (arr, n) => {
    const arrCopy = [...arr];
    if (arrCopy.length <= n)
      return arrCopy;
    // Shuffle array
    for (let i = arrCopy.length - 1; i > 0; i--) {
      const j = Math.floor(Math.random() * (i + 1));
      [arrCopy[i], arrCopy[j]] = [arrCopy[j], arrCopy[i]]; // ES6 array element swap
    }
    return arrCopy.slice(0, n);
  };

  handleCheckboxChange(event) {
    const { id, checked } = event.target;
    this.setState(prevState => ({
      checkboxValues: {
        ...prevState.checkboxValues,
        [id]: checked
      }
    }));
    console.log(this.state.checkboxValues);
  }

  downloadFile = index => {
    if (index === 1) {
      window.scrollTo(0, 0);  
      //output
      this.setState(prevState => ({
        output: [
          ...prevState.output,
          "\n\n\n\nTOP-1\n\n",
          ...this.state.topSamples.map((item, i) => [
            item.map(x => x),
            prevState.checkboxValues[`myCheckbox${i}`],
            "\n"
          ]),
          ...this.state.topSamplel.map((item, i) => [
            item.map(x => x),
            prevState.checkboxValues[`myCheckbox${i+this.state.topSamples.length}`],
            "\n"
          ]),
        ]
      }), () => {
        console.log(this.state.checkboxValues); // Now this will log the updated state
      });

      let checkboxValues = {};
      for (let i = 0; i < 10; i++) {
        checkboxValues[`myCheckbox${i}`] = false;
      }
      this.setState({
        checkboxValues: checkboxValues
      });

      //top-5 points
      const top5 = [];
      for(let i = 0; i < 5; ++i)
        top5.push(this.trs[i]);
      //obtain the index
      const top5small = [], top5large = [];
      for (let i = 5; i < this.props.leftPoints.length; ++i) 
      {
        if ((this.props.scores[4] - this.props.scores[i]) / this.props.scores[4] < 0.1)
          top5small.push(this.pointsScoreRanking[i]);
        else
          top5large.push(this.pointsScoreRanking[i]);
      }
      const top5smallSample = [], top5largeSample = [];
      for (let i = 1; i < 6 && i < top5small.length; ++i)
      {
        let indexx = Math.floor(i/5 * top5small.length - 1);
        if(indexx >= 0)
            top5smallSample.push(top5small[indexx]);
      }
      for (let i = 1; i < 6 && i < top5large.length; ++i)
      {
        let indexx = Math.floor(i/5 * top5large.length - 1);
        if(indexx >= 0)
            top5largeSample.push(top5large[indexx]);
      }

      this.setState({
        intro: "According to our learning algorithm, we found that your top-5 favorite cars are shown as follows.",
        inst1: "Although we know your favorite top-5 cars, we also want to see whether you are interested in some cars outside your top-5 favorite cars. Thus, we select the following cars which are not your top-5 favorite cars. They may be interesting to you. Please COMPARE your favorite top-5 cars shown above and the following cars, and indicate if you are interested in the following cars (in addition to your top-5 favorite cars shown above). You could select 0, one, or more than one cars in which you are interested in the following list.",
        inst2: "We believe that you are NOT interested in the following cars. Please compare your top-5 favorite cars shown above and the following cars, and indicate if you are NOT interested in the following cars? You could select 0, one, or more than one cars in which you are NOT interested in the following list.",
        top: top5,
        topSamples: top5smallSample,
        topSamplel: top5largeSample
      });
    }
    else if(index === 5) {
       window.scrollTo(0, 0);
      //output
      this.state.output.push("\n\n\n\nTOP-5\n\n");
      for(let i = 0; i < this.state.topSamples.length; ++i)
      {
        this.state.output.push(this.state.topSamples[i].map(x => { return (x); }));
        this.state.output.push(this.state.checkboxValues[`myCheckbox${i}`]); //preferred default
        this.state.output.push("\n");
      }
      for(let i = 0; i < this.state.topSamplel.length; ++i)
      {
        this.state.output.push(this.state.topSamplel[i].map(x => { return (x); }));
        this.state.output.push(this.state.checkboxValues[`myCheckbox${i+this.state.topSamples.length}`]); //preferred default
        this.state.output.push("\n");
      }
      let checkboxValues = {};
      for (let i = 0; i < 10; i++) {
        checkboxValues[`myCheckbox${i}`] = false;
      }
      this.setState({
        checkboxValues: checkboxValues
      });

      //top-10 points
      const top10 = [];
      for (let i = 0; i < 10; ++i)
        top10.push(this.trs[i]);
      //obtain the index
      const top10small = [], top10large = [];
      for (let i = 10; i < this.props.leftPoints.length; ++i)
      {
        if ((this.props.scores[9] - this.props.scores[i]) / this.props.scores[9] < 0.1)
          top10small.push(this.pointsScoreRanking[i]);
        else
          top10large.push(this.pointsScoreRanking[i]);
      }

      const top10smallSample = [], top10largeSample = [];
      for (let i = 1; i < 6 && i < top10small.length; ++i)
      {
        let indexx = Math.floor(i/5 * top10small.length - 1);
        if(indexx >= 0)
            top10smallSample.push(top10small[indexx]);
      }
      for (let i = 1; i < 6 && i < top10large.length; ++i)
      {
        let indexx = Math.floor(i/5 * top10large.length - 1);
        if(indexx >= 0)
            top10largeSample.push(top10large[indexx]);
      }

      this.setState({
        intro: "According to our learning algorithm, we found that your top-10 favorite cars are shown as follows.",
        inst1: "Although we know your top-10 favorite cars, in this study, we also want to see whether you are interested in some cars outside your top-10 favorite cars. Thus, we select the following cars which are not your top-10 favorite cars. They may be interesting to you. Please compare your favorite top-10 cars shown above and the following cars, and indicate if you are interested in the following cars (in addition to your favorite top-10 cars shown above). You could select 0, one, or more than one cars in which you are interested in the following list.",
        inst2: "We believe that you are NOT interested in the following cars. Please compare your favorite top-10 cars shown above and the following cars, and indicate if you are NOT interested in the following cars? You could select 0, one, or more than one cars in which you are NOT interested in the following list.",
        top: top10,
        topSamples: top10smallSample,
        topSamplel: top10largeSample
      });
    }
    else
    {
      //output
      this.state.output.push("\n\n\n\nTOP-10\n\n");
      for(let i = 0; i < this.state.topSamples.length; ++i)
      {
        this.state.output.push(this.state.topSamples[i].map(x => { return (x); }));
        this.state.output.push(this.state.checkboxValues[`myCheckbox${i}`]); //preferred default
        this.state.output.push("\n");
      }
      for(let i = 0; i < this.state.topSamplel.length; ++i)
      {
        this.state.output.push(this.state.topSamplel[i].map(x => { return (x); }));
        this.state.output.push(this.state.checkboxValues[`myCheckbox${i+this.state.topSamples.length}`]); //preferred default
        this.state.output.push("\n");
      }
      //let blob = new Blob([this.state.output], {type: 'text/plain'});
      //let url = URL.createObjectURL(blob);
      //let downloadLink = document.createElement('a');
      //downloadLink.href = url;
      //downloadLink.download = 'sample.txt'; // 指定下载文件及类型
      //document.body.appendChild(downloadLink);
      //downloadLink.click();
      //document.body.removeChild(downloadLink);

      let data = {
        text1: this.props.userName,
        text2: this.props.userEmail,
        text3: this.props.interactionResults,
        text4: this.state.output
      };

      
      fetch('http://39.108.168.228:4000/save-text', {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json'
        },
        body: JSON.stringify(data)
      })
          .then(response => response.json())
          .then(data => console.log(data))
          .catch((error) => console.error('Error:', error));
      this.props.showEnd();
    }
  };

  render() {
    const topFivePresentwithbox = this.state.topSamples.map((idx, i) => {
        if (idx) {
            return (
            <tr key={i} data-toggle="tooltip" title={this.props.labels[idx]}>
              <td key={0}>{idx[0]}</td>
              <td key={1}>{idx[1]}</td>
              <td key={2}>{idx[2]}</td>
              <td key={3}>{idx[3]}</td>
              <td>
                <input
                    type="checkbox"
                    id={`myCheckbox${i}`}
                    name={`myCheckbox${i}`}
                    onChange={this.handleCheckboxChange.bind(this)}
                    checked={this.state.checkboxValues[`myCheckbox${i}`]}
                />
              </td>
            </tr>
            )
        } else {
            return null;
        }
    }); 
    const topFivetoTenPresentwithbox = this.state.topSamplel.map((idx, i) => (
        <tr key={i} data-toggle="tooltip" title={this.props.labels[idx]}>
          <td key={0}>{idx[0]}</td>
          <td key={1}>{idx[1]}</td>
          <td key={2}>{idx[2]}</td>
          <td key={3}>{idx[3]}</td>
          <td>
            <input
                type="checkbox"
                id={`myCheckbox${i+this.state.topSamples.length}`}
                name={`myCheckbox${i+this.state.topSamples.length}`}
                onChange={this.handleCheckboxChange.bind(this)}
                checked={this.state.checkboxValues[`myCheckbox${i+this.state.topSamples.length}`]}
            />
          </td>
        </tr>
    ));

    return (
        <div>
          <div className="justify-content-center">
            <h4>{this.state.intro}</h4>
            <table className={classNames("table", "table-hover", {
                     "table-fixed": this.trs.length > 7
                   })}
                   style={{
                     maxWidth: "40rem",
                     margin: "auto"
                   }}>
              <thead>
              <tr>{this.ths}</tr>
              </thead>
              <tbody>{this.state.top}</tbody>
            </table>

            <br></br>
            <h5>{this.state.inst1}</h5>
            <table
                className={classNames("table", "table-hover", {
                  "table-fixed": this.trs.length > 7
                })}
                style={{
                  maxWidth: "40rem",
                  margin: "auto"
                }}
            >
              <thead>
              <tr>{this.ths}</tr>
              </thead>
              <tbody>{topFivePresentwithbox}</tbody>
            </table>
            <br></br>

            <br></br>
            <h5>{this.state.inst2}</h5>
            <table
                className={classNames("table", "table-hover", {
                  "table-fixed": this.trs.length > 7
                })}
                style={{
                  maxWidth: "40rem",
                  margin: "auto"
                }}
            >
              <thead>
              <tr>{this.ths}</tr>
              </thead>
              <tbody>{topFivetoTenPresentwithbox}</tbody>
            </table>
            <br></br>

            <div>
              <button
                  type="button"
                  className="btn btn-primary"
                  style={{width: "8rem"}}
                  onClick={() => this.downloadFile(this.state.top.length)}>
                Finish
              </button>
            </div>
          </div>
        </div>
    );
  }
}

const mapStateToProps = ({
  labels,
  candidates,
  leftPoints,
  attributes,
  mask,
  numLeftPoints,
  scores,
  userName,
  userEmail,
  interactionResults, 
  approU
}) => ({
  labels,
  candidates,
  leftPoints,
  attributes,
  mask,
  numLeftPoints,
  scores,
  userName,
  userEmail,
  interactionResults, 
  approU
});

const mapDispatchToProps = dispatch => ({
  showEnd: () => {
    dispatch(setActiveComponent("End"));
    dispatch(restart());
  }
});

export default connect(
  mapStateToProps,
  mapDispatchToProps
)(Result);
