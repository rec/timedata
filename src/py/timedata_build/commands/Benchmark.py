from . Command import *


class Benchmark(Command):
    description = 'Run benchmark'

    def run(self):
        print('Benchmark')
        name = FLAGS.name
        if not name:
            parts = [FLAGS.build_type]
            for o in FLAGS.compileropt.split():
                parts.append(o[2:])
            name = '_'.join(parts)

        from benchmark.benchmark import run_benchmarks
        run_benchmarks(FLAGS.benchmarks.split(','), '-'.join(parts),
                       FLAGS.benchmark_size, FLAGS.benchmark_number)
